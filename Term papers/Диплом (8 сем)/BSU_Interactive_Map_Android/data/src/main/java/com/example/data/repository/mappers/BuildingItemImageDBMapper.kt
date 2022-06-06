package com.example.data.repository.mappers

import com.example.data.roomDB.entities.buildingItem.buildingItemImage.BuildingItemImageEntityDB
import com.example.domain.BuildingItemImage

// This mapper converts a database entity to a domain entity
class BuildingItemImageDBMapper {

    fun fromDBToDomain(item: BuildingItemImageEntityDB?) : BuildingItemImage? {
        return if (item == null) {
            null
        } else {
            BuildingItemImage(item.id,
                item.description,
                item.imagePath)
        }
    }

}