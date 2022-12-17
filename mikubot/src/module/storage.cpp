#include "module/modulemanager.hpp"
#include "command/command.hpp"

#include "client.hpp"
#include "mikubot.hpp"
#include "util/num.hpp"

#include <functional>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class Storage : public Module
{
public:
    const std::string desc() const override { return "storage functionality. add, grab, and delete files."; }

    void init() override;
public:
    Status uploadAttachment(const std::string& attachUrl, const uint64_t uuid, const std::string& path);
    MethodReturn<const std::string> grabFile(const uint64_t uuid, const std::string& path);
    Status removeFile(const uint64_t uuid, const std::string& path);
    MethodReturn<const std::string> getTree(const uint64_t uuid);
private:

};

DEFINE_MODULE(Storage);

SETUP_COMMAND(Store, Storage, "store", "add new files to personal or server storage.")
{
    addOption("location", "where to store the file", Option::STRING, true)
        .addChoice("personal", "personal")
        .addChoice("server", "server");
    addOption("file", "the file to store", Option::ATTACHMENT, true);
    addOption("path", "the path to the directory to write the file to", Option::STRING);
}

SETUP_COMMAND(Remove, Storage, "rm", "remove files and directories.")
{
    addOption("location", "where the file is stored", Option::STRING)
        .addChoice("personal", "personal")
        .addChoice("server", "server");
    addOption("path", "the full path of the file", Option::STRING);
}

SETUP_COMMAND(Grab, Storage, "grab", "grab files.")
{
    addOption("location", "where the file is stored", Option::STRING, true)
        .addChoice("personal", "personal")
        .addChoice("server", "server");
    addOption("path", "the full path of the file", Option::STRING, true);
}

SETUP_COMMAND(Tree, Storage, "tree", "show a tree of all files.")
{
    addOption("location", "the storage location to show", Option::STRING, true)
        .addChoice("personal", "personal")
        .addChoice("server", "server");
}

COMMAND(Store)
{
    const dpp::attachment& attachment = ctx.command.get_resolved_attachment(ARG("file", dpp::snowflake));
    const dpp::snowflake& uuid = ARG("location", std::string) == "personal" ? 
        ctx.command.usr.id : ctx.command.guild_id;

    std::string path;
    if(!HAS_ARG("path"))
        path = attachment.filename;
    else
        path = ARG("path", std::string) + attachment.filename;

    Module::Status res = m_module->uploadAttachment(attachment.url, uuid, path);
    if(res.code != Module::Status::OK)
        ctx.reply(res.msg);
    else
        ctx.reply("file `" + path + "` uploaded to " + ARG("location", std::string) + " storage");
}

COMMAND(Remove)
{
    const dpp::snowflake& uuid = ARG("location", std::string) == "personal" ? 
        ctx.command.usr.id : ctx.command.guild_id;
   
    const std::string& path = ARG("path", std::string);

    const Module::Status res = m_module->removeFile(uuid, path);
    ctx.reply(res.msg);
}

COMMAND(Grab)
{
    const dpp::snowflake& uuid = ARG("location", std::string) == "personal" ? 
        ctx.command.usr.id : ctx.command.guild_id;
   
    // if successful, holds file binary in data property
    const Module::MethodReturn<const std::string> res = m_module->grabFile(uuid, ARG("path", std::string));
    if(res.code != Module::Status::OK)
    {
        ctx.reply(res.msg);
        return;
    }

    dpp::message response;
    response.add_file(fs::path(ARG("path", std::string)).filename(), res.data);

    ctx.reply(response);
}

COMMAND(Tree)
{
    const dpp::snowflake& uuid = ARG("location", std::string) == "personal" ?
        ctx.command.usr.id : ctx.command.guild_id;

    const Module::MethodReturn<const std::string> res = m_module->getTree(uuid);
    if(res.code != Module::Status::OK)
        ctx.reply(res.msg);
    else
        ctx.reply("```" + res.data + "```");
}

void Storage::init()
{
    addCommand(StoreCommand::make(this));
    addCommand(GrabCommand::make(this));
    addCommand(RemoveCommand::make(this));
    addCommand(TreeCommand::make(this));
}

Module::Status Storage::uploadAttachment(const std::string& attachUrl, const uint64_t uuid, const std::string& path)
{
    Client::StringResponse attachRes = Client::sendExternalGet(attachUrl);

    Client::Headers headers;
    headers.push_back("uuid: " + std::to_string(uuid));
    headers.push_back("path: " + path);
    headers.push_back("content-type: octet-stream");

    Client::Response res = Client::sendPost("/upload", attachRes.data, headers);
    if(res.code != Client::Response::OK)
        return { Status::NOT_OK, res.data };

    return { Status::OK, "" };
}

Module::MethodReturn<const std::string> Storage::grabFile(const uint64_t uuid, const std::string& path)
{
    Client::Headers headers;
    headers.push_back("uuid: " + std::to_string(uuid));
    headers.push_back("path: " + path);

    const Client::StringResponse res = Client::sendGetStr("/grab", headers);
    if(res.code != Client::Response::OK)
        return { Status::NOT_OK, res.data };

    // return file data 
    return { Status::OK, "", res.data };
}

Module::Status Storage::removeFile(const uint64_t uuid, const std::string& path)
{
    Client::Headers headers;
    headers.push_back("uuid: " + std::to_string(uuid));

    Client::StringResponse res = Client::sendPostStr("/rm", path, headers);
    if(res.code != Client::Response::OK)
        return { Status::NOT_OK, res.data };

    return { Status::OK, res.data };
}

Module::MethodReturn<const std::string> Storage::getTree(const uint64_t uuid)
{
    const Client::Headers headers = {"uuid: " + std::to_string(uuid)};

    const Client::StringResponse res = Client::sendGetStr("/tree", headers);
    if(res.code != Client::Response::OK)
        return { Status::NOT_OK, res.data };
    
    return { Status::OK, "", res.data };
}

