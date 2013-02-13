#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <stdexcept>

/**
 * https://svn.boost.org/trac/boost/ticket/1976#comment:2
 * 
 * "The idea: uncomplete(/foo/new, /foo/bar) => ../new
 *  The use case for this is any time you get a full path (from an open dialog, perhaps)
 *  and want to store a relative path so that the group of files can be moved to a different
 *  directory without breaking the paths. An IDE would be a simple example, so that the
 *  project file could be safely checked out of subversion."
 * 
 * ALGORITHM:
 *  iterate path and base
 * compare all elements so far of path and base
 * whilst they are the same, no write to output
 * when they change, or one runs out:
 *   write to output, ../ times the number of remaining elements in base
 *   write to output, the remaining elements in path
 */
boost::filesystem::path
naive_uncomplete(boost::filesystem::path const p, boost::filesystem::path const base) {

    using boost::filesystem::path;
    using boost::filesystem::dot;
    using boost::filesystem::slash;

    if (p == base)
        return "./";
        /*!! this breaks stuff if path is a filename rather than a directory,
             which it most likely is... but then base shouldn't be a filename so... */

    boost::filesystem::path from_path, from_base, output;

    boost::filesystem::path::iterator path_it = p.begin(),    path_end = p.end();
    boost::filesystem::path::iterator base_it = base.begin(), base_end = base.end();

    // check for emptiness
    if ((path_it == path_end) || (base_it == base_end))
        throw std::runtime_error("path or base was empty; couldn't generate relative path");

#ifdef WIN32
    // drive letters are different; don't generate a relative path
    if (*path_it != *base_it)
        return p;

    // now advance past drive letters; relative paths should only go up
    // to the root of the drive and not past it
    ++path_it, ++base_it;
#endif

    // Cache system-dependent dot, double-dot and slash strings
    const String _dot  = String(1, dot<path>::value);
    const String _dots = String(2, dot<path>::value);
    const String _sep = String(1, slash<path>::value);

    // iterate over path and base
    while (true) {

        // compare all elements so far of path and base to find greatest common root;
        // when elements of path and base differ, or run out:
        if ((path_it == path_end) || (base_it == base_end) || (*path_it != *base_it)) {

            // write to output, ../ times the number of remaining elements in base;
            // this is how far we've had to come down the tree from base to get to the common root
            for (; base_it != base_end; ++base_it) {
                if (*base_it == _dot)
                    continue;
                else if (*base_it == _sep)
                    continue;

                output /= "../";
            }

            // write to output, the remaining elements in path;
            // this is the path relative from the common root
            boost::filesystem::path::iterator path_it_start = path_it;
            for (; path_it != path_end; ++path_it) {

                if (path_it != path_it_start)
                    output /= "/";

                if (*path_it == _dot)
                    continue;
                if (*path_it == _sep)
                    continue;

                output /= *path_it;
            }

            break;
        }

        // add directory level to both paths and continue iteration
        from_path /= path(*path_it);
        from_base /= path(*base_it);

        ++path_it, ++base_it;
    }

    return output;