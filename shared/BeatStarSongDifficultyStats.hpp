#pragma once

#include "songdatacore/shared/patched_bindings.hpp"
#include <string_view>
#include <vector>

namespace SDC_wrapper {
    class BeatStarSongDifficultyStats : public song_data_core::BeatStarSongDifficultyStats
    {
        public:
            /// @brief gets all the requirements as a vector
            /// @return vector filled with each requirement as a string
            [[nodiscard]] std::vector<std::string> GetRequirementVector() const
            {
                int len = BeatStarSongDifficultyStats_requirementsLen(this);
                std::vector<std::string> result;
                result.reserve(len);
                for (int i = 0; i < len; i++)
                {
                    result.emplace_back(BeatStarSongDifficultyStats_requirementsGet(this, i)->string_data);
                }

                return result;
            }

            /// @brief gets the name string as a string view
            [[nodiscard]] inline const std::string_view GetName() const
            {
                return diff.string_data;
            }
    };
}