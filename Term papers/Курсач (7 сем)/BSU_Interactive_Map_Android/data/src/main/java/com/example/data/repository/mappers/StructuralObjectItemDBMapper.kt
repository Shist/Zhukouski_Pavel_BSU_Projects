package com.example.data.repository.mappers

import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.StructuralObjectItemDB
import com.example.domain.StructuralObjectItem

class StructuralObjectItemDBMapper {

    fun fromDBToDomain(item: StructuralObjectItemDB?) : StructuralObjectItem? {
        return if (item == null) {
            null
        } else {
            StructuralObjectItem(item.structuralItemsEntityDB.id,
                item.structuralItemsEntityDB.subdivision,
                item.structuralItemsEntityDB.description,
                item.structuralItemsEntityDB.website,
                item.structuralItemsEntityDB.buildingItemId,
                item.structuralItemsEntityDB.category,
                IconItemDBMapper().fromDBToDomain(item.icon))
        }
    }

}