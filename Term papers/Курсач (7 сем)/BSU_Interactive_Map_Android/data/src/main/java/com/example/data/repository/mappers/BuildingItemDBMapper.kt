package com.example.data.repository.mappers

import com.example.data.roomDB.entities.buildingItem.BuildingItemDB
import com.example.domain.BuildingItem
import com.example.domain.IconItem
import com.example.domain.StructuralObjectItem
import java.lang.IndexOutOfBoundsException

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

            if (structuralObjectsEntities != null && iconEntities != null)
            {
                if (structuralObjectsEntities.size == iconEntities.size)
                { // In theory, the API should come like this (amount of StrObjects = amount of icons)
                    for (itemIndex in structuralObjectsEntities.indices)
                    {
                        val curStrObjEntity = structuralObjectsEntities[itemIndex]
                        val curIconEntity = iconEntities[itemIndex]
                        val nextItem = StructuralObjectItem(curStrObjEntity.id,
                            curStrObjEntity.subdivision,
                            curStrObjEntity.description,
                            curStrObjEntity.website,
                            curStrObjEntity.buildingItemId,
                            curStrObjEntity.category,
                            IconItem(curIconEntity.id,
                                curIconEntity.subdivision,
                                curIconEntity.logoPath))
                        structuralObjects += nextItem
                    }
                }
            }

            return BuildingItem(item.buildingItemEntityDB.id,
                structuralObjects.toList(),
                item.buildingItemEntityDB.inventoryUsrreNumber,
                item.buildingItemEntityDB.name,
                item.buildingItemEntityDB.isModern,
                AddressItemDBMapper().fromDBToDomain(item.address),
                item.buildingItemEntityDB.type,
                item.buildingItemEntityDB.markerPath)
        }
    }

}