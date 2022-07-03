include(FetchContent)

# googletest
FetchContent_Declare(googletest
	URL      https://github.com/google/googletest/archive/refs/tags/release-1.12.0.tar.gz
	URL_HASH SHA256=2a4f11dce6188b256f3650061525d0fe352069e5c162452818efbbf8d0b5fe1c
)
FetchContent_MakeAvailable(googletest)

# ryml
FetchContent_Declare(ryml
	URL https://github.com/biojppm/rapidyaml/releases/download/v0.4.1/rapidyaml-0.4.1-src.tgz
	URL_HASH SHA256=3c0a671a7a5aab972f7d259736d14beb9f428c4441f0c220dc0717a4946b495c
)
FetchContent_MakeAvailable(ryml)

