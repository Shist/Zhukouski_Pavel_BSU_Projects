#include "AuthService.hpp"
#include <Shared/MD5.hpp>

#include <fstream>
#include <unordered_map>
#include <boost/log/trivial.hpp>

namespace std
{
template <> struct hash <MD5::Hash>
{
    uint32_t operator() (const MD5::Hash &hash) const
    {
        return std::hash <std::string> () ({(const char *) &hash[0], hash.size ()});
    }
};
}

namespace
{
std::unordered_map <MD5::Hash, MD5::Hash> loginPasswordHashes {};
}

bool AuthService::Check (const std::string &login, const std::string &password)
{
    if (loginPasswordHashes.empty ())
    {
#define AUTH_FILE_NAME "auth.hashes"
        std::ifstream hashesFile (AUTH_FILE_NAME, std::ifstream::binary);

        if (hashesFile)
        {
            uint32_t hashesCount = 0;
            MD5::Hash loginHash;
            MD5::Hash passwordHash;

            // Auth hashes file always uses little endian.
            for (uint32_t index = 0; index < sizeof (hashesCount); ++index)
            {
                if (!hashesFile)
                {
                    BOOST_LOG_TRIVIAL (debug) <<
                                              "AuthService: Auth hashes file size is less than required counted size!";

                    hashesCount = 0;
                    break;
                }

                hashesCount |= ((uint32_t) hashesFile.get () & 0xFFU) << (index * 8);
            }

            BOOST_LOG_TRIVIAL (debug) << "AuthService: Reading " << hashesCount << " hashes...";
            while (hashesCount > 0)
            {
                hashesFile.read ((char *) &loginHash[0], loginHash.size ());
                if (!hashesFile)
                {
                    BOOST_LOG_TRIVIAL (error) << "AuthService: Unable to continue reading auth data, aborting...";
                    break;
                }

                hashesFile.read ((char *) &passwordHash[0], passwordHash.size ());
                loginPasswordHashes[loginHash] = passwordHash;
                --hashesCount;
            }
        }
        else
        {
            BOOST_LOG_TRIVIAL (debug) << "AuthService: Unable to open " << AUTH_FILE_NAME << " file!";
        }
    }

    auto iterator = loginPasswordHashes.find (MD5::FromString (login));
    bool result = iterator != loginPasswordHashes.end () && iterator->second == MD5::FromString (password);

    BOOST_LOG_TRIVIAL (debug) << "AuthService: Received login \"" << login << "\" and password \"" << password <<
                              "\". Check result: " << (result ? "approved" : "declined") << ".";
    return result;
}
