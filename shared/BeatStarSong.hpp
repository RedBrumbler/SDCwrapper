#pragma once

#include "songdatacore/shared/patched_bindings.hpp"
#include "BeatStarSongDifficultyStats.hpp"
#include "BeatStarCharacteristic.hpp"
#include <string_view>
#include<vector>
#include <exception>

constexpr const int beatsaverEpoch = 0;

namespace SDC_wrapper {
    class BeatStarSong : public song_data_core::BeatStarSong
    {
        public:
            /// @brief gets the song for a specific hash
            /// @param hash the song hash tot check on
            /// @return const BeatStarSong* or nullptr for not found
            static inline const BeatStarSong* GetSong(std::string_view hash)
            {
                return reinterpret_cast<const SDC_wrapper::BeatStarSong*>(song_data_core::Beatstar_GetSong(hash.data()));
            }

            /// @brief Gets all songs in a vector
            /// @return vector const BeatStarSong*
            /// @throw std::runtime_error if database failed to parse or failed to download
            static std::vector<const BeatStarSong*> GetAllSongs()
            {
                auto db = song_data_core::Beatstar_RetrieveDatabase();
                if (db == nullptr) {
                    throw std::runtime_error("Database was nullptr, do you have internet?");
                }
                long long len = song_data_core::BeatStarDataFile_map_SongsLen(db);
                std::vector<const BeatStarSong*> res(len);
                for (long long i = 0; i < len; i++)
                {
                    auto key = song_data_core::BeatStarDataFile_map_SongsGetKey(db, i);
                    res[i] = reinterpret_cast<const SDC_wrapper::BeatStarSong*>(song_data_core::BeatStarDataFile_map_SongsGet(db, key));
                }

                return res;
            }

            /// @brief gets difficulty at index
            /// @param idx the index to get at
            /// @return const BeatStarSongDifficultyStats*
            [[nodiscard]] inline const BeatStarSongDifficultyStats* GetDifficulty(int idx) const
            {
                return reinterpret_cast<const BeatStarSongDifficultyStats*>(song_data_core::BeatStarSong_DiffGet(this, idx));
            }

            /// @brief gets difficulty for specific characteristic at idx
            /// @param characteristic the characteristic to check on
            /// @param idx the difficulty for characteristic idx you want
            /// @return const BeatStarSongDifficultyStats*
            [[nodiscard]] const BeatStarSongDifficultyStats* GetDifficulty(const song_data_core::BeatStarCharacteristics& characteristic, int idx) const
            {
                const char* key = song_data_core::BeatStarSong_map_Characteristics_DifficultyStatsGetStrKey(this, characteristic, idx);
                return reinterpret_cast<const BeatStarSongDifficultyStats*>(song_data_core::BeatStarSong_map_Characteristics_DifficultyStatsGet(this, characteristic, key));
            }

            /// @brief inline equivalent for the wrapped characteristic type in this wrapper lib
            /// @param characteristic the characteristic to check on
            /// @param idx the difficulty for characteristic idx you want
            /// @return const BeatStarSongDifficultyStats*
            [[nodiscard]] inline const BeatStarSongDifficultyStats* GetDifficulty(const BeatStarCharacteristic& characteristic, int idx) const
            {
                return GetDifficulty(characteristic.characteristic, idx);
            }

            /// @brief gets the difficulty with a specific name for a characteristic
            /// @param characteristic the characteristic to check on
            /// @param name the name of the difficulty to check for
            /// @return const BeatStarSongDifficultyStats* or nullptr for not found
            [[nodiscard]] const BeatStarSongDifficultyStats* GetDifficulty(const song_data_core::BeatStarCharacteristics& characteristic, std::string_view name) const
            {
                int charLen = song_data_core::BeatStarSong_map_Characteristics_DifficultyStatsLen(this, characteristic);
                for (int i = 0; i < charLen; i++)
                {
                    auto diff = GetDifficulty(characteristic, i);
                    if (!diff) continue;
                    if (diff->GetName() == name) return diff;
                }
                return nullptr;
            }

            /// @brief inline equivalent for the wrapped characteristic type in this wrapper lib
            /// @param characteristic the characteristic to check on
            /// @param name the name of the difficulty to check for
            /// @return const BeatStarSongDifficultyStats* or nullptr for not found
            [[nodiscard]] inline const BeatStarSongDifficultyStats* GetDifficulty(const BeatStarCharacteristic& characteristic, std::string_view name) const
            {
                return GetDifficulty(characteristic.characteristic, name);
            }

            /// @brief gets the entire difficulty vector for all characteristics
            /// @return vector const BeatStarSongDifficultyStats* of every diff
            [[nodiscard]] std::vector<const BeatStarSongDifficultyStats*> GetDifficultyVector() const
            {
                int difflen = song_data_core::BeatStarSong_DiffLen(this);
                std::vector<const BeatStarSongDifficultyStats*> result(difflen);
                for (int i = 0; i < difflen; i++)
                {
                    result[i] = GetDifficulty(i);
                }

                return result;
            }

            /// @brief gets the max NJS for the song
            /// @return highest NJS on all diffs
            [[nodiscard]] float GetMaxNJS() const
            {
                auto diffVec = GetDifficultyVector();
                float max = 0.0f;
                for (auto diff : diffVec)
                {
                    if (diff->njs > max) max = diff->njs;
                }
                return max;
            }

            /// @brief gets the max pp for the song
            /// @return highest pp on all diffs
            [[nodiscard]] double GetMaxPpValue() const
            {
                auto diffVec = GetDifficultyVector();
                double max = 0.0f;
                for (auto diff : diffVec)
                {
                    if (diff->approximate_pp_value > max) max = diff->approximate_pp_value;
                }

                return max;
            }

            /// @brief gets the max star value for the song
            /// @return highest star value on all diffs
            [[nodiscard]] double GetMaxStarValue() const
            {
                auto diffVec = GetDifficultyVector();
                double max = 0.0f;
                for (auto diff : diffVec) 
                {
                    if (diff->stars > max) max = diff->stars;
                }
                return max;
            }

            /// @brief gets the min star value for the song
            /// @return lowest star value on all diffs
            double GetMinStarValue() const
            {
                auto diffVec = GetDifficultyVector();
                double min = -1.0f;
                for (auto diff : diffVec) 
                {
                    if (diff->stars > 0 && (min < 0 || diff->stars < min)) min = diff->stars;
                }
                return min;
            }

            /// @brief Gets the rating for the song
            /// @return float song rating
            [[nodiscard]] inline float GetRating() const
            {
                return song_data_core::BeatStarSong_rating(this);
            }

            /// @brief gets the name as a string view
            [[nodiscard]] inline const std::string_view GetName() const
            {
                return song_name.string_data;
            }

            /// @brief gets the subname as a string view
            [[nodiscard]] inline const std::string_view GetSubName() const
            {
                return song_sub_name.string_data;
            }

            /// @brief gets the songauthor as a string view
            [[nodiscard]] inline const std::string_view GetSongAuthor() const
            {
                return song_author_name.string_data;
            }

            /// @brief gets the mapauthor as a string view
            [[nodiscard]] inline const std::string_view GetAuthor() const
            {
                return level_author_name.string_data;
            }

            /// @brief gets the uploaded string as a string view
            [[nodiscard]] inline const std::string_view GetUploaded() const
            {
                return uploaded.string_data;
            }

            /// @brief gets the hash as a string view
            [[nodiscard]] inline const std::string_view GetHash() const
            {
                return hash.string_data;
            }
    };
}
