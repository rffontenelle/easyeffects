/*
 *  Copyright © 2017-2022 Wellington Wallace
 *
 *  This file is part of EasyEffects.
 *
 *  EasyEffects is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  EasyEffects is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with EasyEffects.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "loudness_preset.hpp"

LoudnessPreset::LoudnessPreset() {
  input_settings = g_settings_new_with_path(preset_id.c_str(), (tags::app::path + "/streaminputs/loudness/").c_str());

  output_settings = g_settings_new_with_path(preset_id.c_str(), (tags::app::path + "/streamoutputs/loudness/").c_str());
}

void LoudnessPreset::save(nlohmann::json& json, const std::string& section, GSettings* settings) {
  json[section]["loudness"]["input-gain"] = g_settings_get_double(settings, "input-gain");

  json[section]["loudness"]["output-gain"] = g_settings_get_double(settings, "output-gain");

  json[section]["loudness"]["fft"] = util::gsettings_get_string(settings, "fft");

  json[section]["loudness"]["std"] = util::gsettings_get_string(settings, "std");

  json[section]["loudness"]["volume"] = g_settings_get_double(settings, "volume");
}

void LoudnessPreset::load(const nlohmann::json& json, const std::string& section, GSettings* settings) {
  update_key<double>(json.at(section).at("loudness"), settings, "input-gain", "input-gain");

  update_key<double>(json.at(section).at("loudness"), settings, "output-gain", "output-gain");

  update_key<gchar*>(json.at(section).at("loudness"), settings, "fft", "fft");

  update_key<gchar*>(json.at(section).at("loudness"), settings, "std", "std");

  update_key<double>(json.at(section).at("loudness"), settings, "volume", "volume");
}
