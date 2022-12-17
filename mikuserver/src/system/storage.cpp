#include "system/system.hpp"

#include "mikuserver.hpp"
#include "system/systemmanager.hpp"
#include "resource.hpp"
#include "response.hpp"

#include <fstream>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

class Storage : public System
{
public:
    void init() override;
    
    Status createFile(const std::string& uuid, const std::string& data, const std::string& path);
    MethodReturn<const std::string> grabFile(const std::string& uuid, const std::string& path);
    Status removeFile(const std::string& uuid, const std::string& path);
    MethodReturn<const std::string> createTree(const std::string& uuid);
private:
    void collectTreeItems(const fs::path& dir, std::stringstream& tree, uint8_t level = 0);
};

DEFINE_SYSTEM(Storage)

RESOURCE("/upload", Storage, Upload, POST)
{
    if(!MikuServer::verifyRequest(req.get_headers()))
        return Response::badAuth();

    FIELD(path);
    FIELD(uuid);  

    const System::Status res = m_system->createFile(uuid, req.get_content(), path);
    if(res.code != System::Status::OK)
        return Response::badReq(res.msg);
    
    return std::shared_ptr<http_response>(new string_response("{}"));
}

RESOURCE("/grab", Storage, Grab, GET)
{
    if(!MikuServer::verifyRequest(req.get_headers()))
        return Response::badAuth();

    FIELD(path);
    FIELD(uuid);

    const System::MethodReturn<const std::string> res = m_system->grabFile(uuid, path);
    if(res.code != System::Status::OK)
        return Response::badReq(res.msg);

    return std::shared_ptr<http_response>(new string_response(res.data));
}

RESOURCE("/rm", Storage, Remove, POST)
{
    if(!MikuServer::verifyRequest(req.get_headers()))
        return Response::badAuth();

    FIELD(uuid);
    
    const System::Status res = m_system->removeFile(uuid, req.get_content());
    if(res.code != System::Status::OK)
        return Response::badReq(res.msg);

    return std::shared_ptr<http_response>(new string_response(res.msg));
}

RESOURCE("/tree", Storage, Tree, GET)
{
    if(!MikuServer::verifyRequest(req.get_headers()))
        return Response::badAuth();

    FIELD(uuid);

    const System::MethodReturn<const std::string> res = m_system->createTree(uuid);
    if(res.code != System::Status::OK)
        return Response::badReq(res.msg);

    return std::shared_ptr<http_response>(new string_response(res.data));
}

void Storage::init()
{
    addResource(UploadResource::make(this));
    addResource(GrabResource::make(this));
    addResource(RemoveResource::make(this));
    addResource(TreeResource::make(this));
}

System::Status Storage::createFile(const std::string& uuid, const std::string& data, const std::string& path)
{
    const fs::path storePath = fs::path("./store/" + uuid + "/" + path);
    if(fs::exists(storePath))
        return { Status::NOT_OK, "file already exists!" };

    fs::create_directories(storePath.parent_path());
    
    std::ofstream ofs(storePath.string());
    ofs << data;
    ofs.close();

    return { Status::OK };
}

System::MethodReturn<const std::string> Storage::grabFile(const std::string& uuid, const std::string& path)
{
    const std::string storePath = "./store/" + uuid + "/" + path;
    if(!fs::exists(storePath))
        return { Status::NOT_OK, "file doesn't exist!" };

    std::ifstream ifs(storePath, std::ios::binary);
    std::stringstream ss;
    ss << ifs.rdbuf();
    
    return { Status::OK, "", ss.str() };
}

System::Status Storage::removeFile(const std::string& uuid, const std::string& path)
{
    const fs::path storePath = fs::path("./store/" + uuid + "/" + path);
    if(!fs::exists(storePath))
        return { Status::NOT_OK, "file doesn't exist!" };

    const std::uintmax_t res = fs::remove_all(storePath);
    const std::string name = storePath.filename().string();

    std::string msg;
    if(res > 1)
        msg = "removed directory `" + name + "` containing " + std::to_string(res) + " items";
    else
        msg = "removed file `" + name + "`";

    return { Status::OK, msg };
}

System::MethodReturn<const std::string> Storage::createTree(const std::string& uuid)
{
    const fs::path path = fs::path("./store/" + uuid);

    // will also return false if path doesn't exist
    if(fs::is_empty(path))
        return { Status::NOT_OK, "no files to show!" };

    std::stringstream tree; 
    collectTreeItems(path, tree);

    return { Status::OK, "", tree.str() };
}

void Storage::collectTreeItems(const fs::path& dir, std::stringstream& tree, uint8_t level)
{
    for (const fs::directory_entry& item : fs::directory_iterator(dir))
    {
        for(uint8_t i = 0; i < level; i++)
            tree << "     ";
        if(item.is_directory())
        {
            tree << item.path().filename().string() << "/\n";
            collectTreeItems(item.path(), tree, level + 1);
        }
        else
            tree << item.path().filename().string() << '\n';
    }
}
