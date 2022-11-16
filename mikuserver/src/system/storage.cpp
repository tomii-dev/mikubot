#include "system/system.hpp"

#include "system/systemmanager.hpp"
#include "resource.hpp"

class Storage : public System
{
public:
    void init() override;
    
    enum StorageType
    {
        PERSONAL,
        GUILD
    };

    enum FileType
    {
        AUDIO_MP3,
        AUDIO_M4A,
        AUDIO_OGG,
        AUDIO_FLAC,

        IMAGE_PNG,
        IMAGE_JPG,

        VIDEO_MP4,
        VIDEO_MOV,
        VIDEO_AVI,
        
        TEXT
    }

    MethodReturn<void> createFile(StorageType, FileType, uint64_t, void*, const std::string&);
    
private:

};

DEFINE_SYSTEM(Storage)

RESOURCE("/test", Storage, TestResource, GET)
{
    return std::shared_ptr<http_response>(new string_response("test!!"));
}

void Storage::init()
{
    addResource(TestResource::make(this));
}

System::MethodReturn<void> Storage::createFile(StorageType storageType, FileType fileType, uint64_t uuid, void* data, const std::string& path)
{

}
