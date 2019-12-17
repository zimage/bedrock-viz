#include "loader.h"
#include "../logger.h"
#include "load_block.h"
#include "load_biome.h"
#include "load_item.h"

namespace mcpe_viz
{
    int load_xml(const std::string& filepath)
    {
        pugi::xml_document doc;
        auto result = doc.load_file(filepath.c_str());

        if (!result) {
            log::error("xml file({}) not parsed successfully: {}",
                filepath, result.description());
            return -1;
        }

        auto root = doc.child("xml");

        if (load_biome(root.child("biomelist")) != 0) {
            log::error("biomelist parse failed");
            return -1;
        }
        if (load_block(root.child("blocklist")) != 0) {
            log::error("blocklist parse failed");
            return -1;
        }
        if (load_item(root.child("itemlist")) != 0) {
            log::error("itemlist parse failed");
            return -1;
        }

        return 0;
    }
}