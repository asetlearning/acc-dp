# hunter_config(Boost VERSION 1.82.0)

# Download because boost servers are unreliable
hunter_config(
    Boost
    URL https://mathematiq.com/3rdparty/boost_1_83_0.tar.bz2
    SHA1 75b1f569134401d178ad2aaf97a2993898dd7ee3
    KEEP_PACKAGE_SOURCES
)

# newer version to support cmake 4.0
hunter_config(
    nlohmann_json
    URL https://mathematiq.com/3rdparty/json-3.12.0.tar.gz
    SHA1 815212d8acbddc87009667c52ba98a8404efec18
    KEEP_PACKAGE_SOURCES
)
