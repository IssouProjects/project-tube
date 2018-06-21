#include <unordered_map>

using namespace std;

/*! Generic class to manage assets
 *
 *  The AssetManager manages assets (files), with a custom cache mechanism.
 *  It will implement different specializations for different types, to
 *  provide checks and, if needed, more complex mechanisms.
 *
 *  @tparam AssetClass The asset type that this class will handle.
 */
template<typename AssetClass> class AssetManager {
    //! Typedef to avoid the voerbosity of C++
    typedef shared_ptr<AssetClass> spAsset;

    public:

    /*! Constructor for AssetManager
     *
     *  Creates an asset manager with the corresponding base path.
     *
     *  @param base_path Path that will be prepended to all file requests.
     */
    AssetManager(string base_path) : base_path(base_path);

    //! Destructor for AssetManager
    ~AssetManager();

    /*! Loads an asset from the given path and returns a shared_ptr to it
     *
     *  Loads the file from the given path, ensures that it's a valid file (e.g. it's what this instance expects),
     *  and stores it in it's `cache`.
     *  
     *  @param  asset_path String containing the path of the asset (relative to the base pass of this instance)
     *  @return shared_ptr to the loaded asset
     *
     *  @throws runtime_error If the file wasn't found.
     *  @throws runtime_error If the file was found, but it couldn't be loaded (invalid format, invalid content)
     */
    spAsset load(string asset_path);
    
    /*! Cleans this instance's memory
     *
     *  Iterates on every item of the `cache` and removes it if this object has the only reference (e.g. only 1 reference).
     */ 
    void clean();

    //Attributes
    private:
    
    //! Base path prepended to every request for a file.
    string base_path;

    //! Structure to keep the cached assets.
    unordered_map<string, spAsset> cache;
}
