package com.example.data.repository.mappers

import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.StructuralObjectItemEntityDB
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem.IconItemEntityDB
import com.example.domain.StructuralObjectItem

// This mapper converts a database entity to a domain entity
class StructuralObjectItemDBMapper {

    fun fromDBToDomain(itemSO: StructuralObjectItemEntityDB?, itemI: IconItemEntityDB?) : StructuralObjectItem? {
        return if (itemSO == null) {
            null
        } else {
            StructuralObjectItem(itemSO.id,
                itemSO.subdivision,
                itemSO.description,
                itemSO.website,
                itemSO.buildingItemId,
                itemSO.category,
                IconItemDBMapper().fromDBToDomain(itemI))
        }
    }

}