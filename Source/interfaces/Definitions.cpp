#include "definitions.h"

namespace WPEFramework {

struct ScreenResolutionWidthHeight {
    Exchange::IComposition::ScreenResolution resolution;
    uint32_t width;
    uint32_t height;
};

ScreenResolutionWidthHeight resolutionWidthHeightTable[] = {

    { Exchange::IComposition::ScreenResolution_Unknown, 0, 0 },
    { Exchange::IComposition::ScreenResolution_480i, 640, 480 },
    { Exchange::IComposition::ScreenResolution_480p, 640, 480 },
    { Exchange::IComposition::ScreenResolution_720p, 1280, 720 },
    { Exchange::IComposition::ScreenResolution_720p50Hz, 1280, 720 },
    { Exchange::IComposition::ScreenResolution_1080p24Hz, 1920, 1080 },
    { Exchange::IComposition::ScreenResolution_1080i50Hz, 1920, 1080 },
    { Exchange::IComposition::ScreenResolution_1080p50Hz, 1920, 1080 },
    { Exchange::IComposition::ScreenResolution_1080p60Hz, 1920, 1080 },
    { Exchange::IComposition::ScreenResolution_2160p50Hz, 3840, 2160 },
    { Exchange::IComposition::ScreenResolution_2160p60Hz, 3840, 2160 },
};

ENUM_CONVERSION_BEGIN(Exchange::IComposition::ScreenResolution)

    { Exchange::IComposition::ScreenResolution_Unknown, _TXT("Unknown") },
    { Exchange::IComposition::ScreenResolution_480i, _TXT("480i") },
    { Exchange::IComposition::ScreenResolution_480p, _TXT("480p") },
    { Exchange::IComposition::ScreenResolution_720p, _TXT("720p") },
    { Exchange::IComposition::ScreenResolution_720p50Hz, _TXT("720p50Hz") },
    { Exchange::IComposition::ScreenResolution_1080p24Hz, _TXT("1080p24Hz") },
    { Exchange::IComposition::ScreenResolution_1080i50Hz, _TXT("1080i50Hz") },
    { Exchange::IComposition::ScreenResolution_1080p50Hz, _TXT("1080p50Hz") },
    { Exchange::IComposition::ScreenResolution_1080p60Hz, _TXT("1080p60Hz") },
    { Exchange::IComposition::ScreenResolution_2160p50Hz, _TXT("2160p50Hz") },
    { Exchange::IComposition::ScreenResolution_2160p60Hz, _TXT("2160p60Hz") },

ENUM_CONVERSION_END(Exchange::IComposition::ScreenResolution)

ENUM_CONVERSION_BEGIN(Exchange::IStream::streamtype)
    { Exchange::IStream::Undefined,   _TXT("Unknown")     },
    { Exchange::IStream::Cable,       _TXT("Cable")       },
    { Exchange::IStream::Handheld,    _TXT("Handheld")    },
    { Exchange::IStream::Satellite,   _TXT("Satellite")   },
    { Exchange::IStream::Terrestrial, _TXT("Terrestrial") },
    { Exchange::IStream::DAB,         _TXT("DAB")         },
    { Exchange::IStream::RF,          _TXT("RF")          },
    { Exchange::IStream::Unicast,     _TXT("Unicast")     },
    { Exchange::IStream::Multicast,   _TXT("Multicast")   },
    { Exchange::IStream::IP,          _TXT("IP")          },
ENUM_CONVERSION_END(Exchange::IStream::streamtype)

ENUM_CONVERSION_BEGIN(Exchange::IStream::state)
    { Exchange::IStream::Loading,  _TXT("Loading")  },
    { Exchange::IStream::Prepared, _TXT("Prepared") },
    { Exchange::IStream::Paused,   _TXT("Paused")   },
    { Exchange::IStream::Playing,  _TXT("Playing")  },
    { Exchange::IStream::Error,    _TXT("Error")    },
ENUM_CONVERSION_END(Exchange::IStream::state)

namespace Exchange
{

    uint32_t IComposition::WidthFromResolution(const IComposition::ScreenResolution resolution)
    {
        return ((static_cast<uint32_t>(resolution) < sizeof(resolutionWidthHeightTable) / sizeof(ScreenResolutionWidthHeight)) ? resolutionWidthHeightTable[static_cast<uint32_t>(resolution)].width : 0);
    }

    uint32_t IComposition::HeightFromResolution(const IComposition::ScreenResolution resolution)
    {
        return ((static_cast<uint32_t>(resolution) < sizeof(resolutionWidthHeightTable) / sizeof(ScreenResolutionWidthHeight)) ? resolutionWidthHeightTable[static_cast<uint32_t>(resolution)].height : 0);
    }
}
}
