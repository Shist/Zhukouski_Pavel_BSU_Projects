package com.example.data.repository.mappers

import com.example.data.roomDB.entities.buildingItem.BuildingItemDB
import com.example.domain.BuildingItem
import com.example.domain.StructuralObjectItem

// This mapper converts a database entity to a domain entity
class BuildingItemDBMapper {

    fun fromDBToDomain(item: BuildingItemDB?) : BuildingItem? {
        if (item == null) {
            return null
        }
        else {
            val structuralObjects: MutableList<StructuralObjectItem?> =
                emptyList<StructuralObjectItem?>().toMutableList()

            val structuralObjectsEntities = item.structuralObjectEntities
            val iconEntities = item.iconEntities

            if (structuralObjectsEntities != null && iconEntities != null) {
                if (structuralObjectsEntities.size == iconEntities.size)
                { // In theory, the API should come like this (amount of StrObjects = amount of icons)
                    for (itemIndex in structuralObjectsEntities.indices) {
                        val curStrObjEntity = structuralObjectsEntities[itemIndex]
                        val curIconEntity = iconEntities[itemIndex]
                        structuralObjects += StructuralObjectItemDBMapper()
                            .fromDBToDomain(curStrObjEntity, curIconEntity)
                    }
                }
            }

            return BuildingItem(item.buildingItemEntityDB.id,
                structuralObjects.toList(),
                item.buildingItemImageEntities?.map {
                    BuildingItemImageDBMapper().fromDBToDomain(it)
                },
                item.buildingItemEntityDB.inventoryUsrreNumber,
                item.buildingItemEntityDB.name,
                item.buildingItemEntityDB.isModern,
                AddressItemDBMapper().fromDBToDomain(item.address),
                item.buildingItemEntityDB.type,
                item.buildingItemEntityDB.markerPath)
        }
    }

}