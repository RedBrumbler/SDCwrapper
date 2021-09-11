#pragma once

#include "songdatacore/shared/bindings.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include <string>

#if defined __has_include && __has_include("GlobalNamespace/BeatmapCharacteristicSO.hpp")
#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"
#else
namespace GlobalNamespace {
    typedef Il2CppObject BeatmapCharacteristicSO;
}
#endif

namespace SDC_wrapper {
    class BeatStarCharacteristic
    {
        public:
            /// wrapping a characteristic
            song_data_core::BeatStarCharacteristics characteristic = song_data_core::BeatStarCharacteristics::Unknown;
            BeatStarCharacteristic(song_data_core::BeatStarCharacteristics* char_) : characteristic(*char_) {};
            BeatStarCharacteristic(GlobalNamespace::BeatmapCharacteristicSO* char_) : characteristic(BeatmapCharacteristicToBeatStarCharacteristic(char_)) {};

            constexpr BeatStarCharacteristic(const song_data_core::BeatStarCharacteristics& char_) : characteristic(char_) {};
            BeatStarCharacteristic(std::string_view serializedName) : characteristic(StringToBeatStarCharacteristic(serializedName)) {};
            
            /// @brief implicit conversion operator from this type to what song_data_core uses
            operator song_data_core::BeatStarCharacteristics() const { return characteristic; }
            operator const song_data_core::BeatStarCharacteristics*() const { return &characteristic; }

            /// @brief gets the string for the wrapped characteristic
            /// @return string serialized Name
            inline std::string_view ToString() const
            {
                return BeatStarCharacteristicToString(characteristic);
            }

            /// @brief gets the characteristic that belongs with this game SO
            /// @param  char_ characteristicSO to get the characteristic for
            /// @return song_data_core::BeatStarCharacteristics
            static song_data_core::BeatStarCharacteristics BeatmapCharacteristicToBeatStarCharacteristic(GlobalNamespace::BeatmapCharacteristicSO* char_)
            {
                return StringToBeatStarCharacteristics(BeatmapCharacteristicToString(char_));
            }

            /// @brief gets the serializedName from the game object
            /// @param char_ the characteristic SO to get thet name for
            /// @return string serialized name
            static std::string BeatmapCharacteristicToString(GlobalNamespace::BeatmapCharacteristicSO* char_)
            {
                return to_utf8(csstrtostr(CRASH_UNLESS(il2cpp_utils::RunMethod<Il2CppString*>(char_, "get_serializedName"))));
            }

            /// @brief Gets the string that describes the characteristic
            /// @param characteristic the characteristic to check
            /// @return string serialized names
            static std::string_view BeatStarCharacteristicToString(const song_data_core::BeatStarCharacteristics& characteristic)
            {
                switch(characteristic)
                {
                    case song_data_core::BeatStarCharacteristics::Unknown: return "Unknown";
                    case song_data_core::BeatStarCharacteristics::Standard: return "Standard";
                    case song_data_core::BeatStarCharacteristics::OneSaber: return "OneSaber";
                    case song_data_core::BeatStarCharacteristics::NoArrows: return "NoArrows";
                    case song_data_core::BeatStarCharacteristics::Lightshow: return "Lightshow";
                    case song_data_core::BeatStarCharacteristics::Degree90: return "Degree90";
                    case song_data_core::BeatStarCharacteristics::Degree360: return "Degree360";
                    case song_data_core::BeatStarCharacteristics::Lawless: return "Lawless";
                }
            }

            /// @brief Gets the song_data_core::BeatStarCharacteristics from a passed serialized char name
            /// @param serializedName the name to check for
            /// @return song_data_core::BeatStarCharacteristic of the name, or Unknown for invalid
            static song_data_core::BeatStarCharacteristics StringToBeatStarCharacteristics(std::string_view serializedName)
            {
                switch(serializedName.data()[0])
                {
                    case 's': [[fallthrough]];
                    case 'S': return song_data_core::BeatStarCharacteristics::Standard;
                    case 'o': [[fallthrough]];
                    case 'O': return song_data_core::BeatStarCharacteristics::OneSaber;
                    case 'n': [[fallthrough]];
                    case 'N': return song_data_core::BeatStarCharacteristics::NoArrows;
                    case 'd': [[fallthrough]];
                    case 'D':
                        if (serializedName.data()[6] == '9') return song_data_core::BeatStarCharacteristics::Degree90;
                        else return song_data_core::BeatStarCharacteristics::Degree360;
                    case 'l': [[fallthrough]];
                    case 'L': {
                        if (serializedName.data()[1] == 'a' || serializedName.data()[1] == 'A') return song_data_core::BeatStarCharacteristics::Lawless;
                        else return song_data_core::BeatStarCharacteristics::Lightshow;
                    }
                    default: return song_data_core::BeatStarCharacteristics::Unknown;
                }
            }

            /// @brief gets a SDC_wrapper::BeatStarCharacteristic from the passed serialized Name
            /// @param serializedName name to check for
            /// @return wrapped song_data_core BeatStarCharacteristic
            static BeatStarCharacteristic StringToBeatStarCharacteristic(std::string_view serializedName)
            {
                return StringToBeatStarCharacteristics(serializedName);
            }

            // some constexpr automatic wrapper makers, could be useful

            /// @brief constexpr returns a wrapped song_data_core::BeatStarCharacteristics::Unknown
            static constexpr BeatStarCharacteristic Unknown() { return song_data_core::BeatStarCharacteristics::Unknown; };
            
            /// @brief constexpr returns a wrapped song_data_core::BeatStarCharacteristics::Standard
            static constexpr BeatStarCharacteristic Standard() { return song_data_core::BeatStarCharacteristics::Standard; };
            
            /// @brief constexpr returns a wrapped song_data_core::BeatStarCharacteristics::OneSaber
            static constexpr BeatStarCharacteristic OneSaber() { return song_data_core::BeatStarCharacteristics::OneSaber; };
            
            /// @brief constexpr returns a wrapped song_data_core::BeatStarCharacteristics::NoArrows
            static constexpr BeatStarCharacteristic NoArrows() { return song_data_core::BeatStarCharacteristics::NoArrows; };
            
            /// @brief constexpr returns a wrapped song_data_core::BeatStarCharacteristics::Lightshow
            static constexpr BeatStarCharacteristic Lightshow() { return song_data_core::BeatStarCharacteristics::Lightshow; };
            
            /// @brief constexpr returns a wrapped song_data_core::BeatStarCharacteristics::Degree90
            static constexpr BeatStarCharacteristic Degree90() { return song_data_core::BeatStarCharacteristics::Degree90; };
            
            /// @brief constexpr returns a wrapped song_data_core::BeatStarCharacteristics::Degree360
            static constexpr BeatStarCharacteristic Degree360() { return song_data_core::BeatStarCharacteristics::Degree360; };
            
            /// @brief constexpr returns a wrapped song_data_core::BeatStarCharacteristics::Lawless
            static constexpr BeatStarCharacteristic Lawless() { return song_data_core::BeatStarCharacteristics::Lawless; };
    };
    
}