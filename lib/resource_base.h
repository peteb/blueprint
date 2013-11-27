#ifndef _RESOURCE_BASE_H_
#define _RESOURCE_BASE_H_

// Resource handler class, taking care of textures, images, and audio.

namespace res
{

//--------------------------------------------------------------------

    namespace Textures
    {
        enum ID
        {
            WORLD_TILES = 0
        }
    }

//--------------------------------------------------------------------

    template <typename T>
    class ResourceBase
    {
    public:
        ResourceBase();
        ~ResourceBase();
        
        void load( T::ID, 
    private:
    };

}

#endif // _RESOURCE_BASE_H_
