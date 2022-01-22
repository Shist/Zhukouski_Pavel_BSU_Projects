package com.example.data.roomDB.entities.buildingItem

import com.example.data.model.BuildingItemJson
import com.example.data.roomDB.entities.buildingItem.adressItem.AddressItemJsonMapper
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.StructuralObjectItemJsonMapper

class BuildingItemJsonMapper {

    fun fromJsonToRoomDB(itemJson: BuildingItemJson?) : BuildingItemDB?
    {
        if (itemJson == null) {
            return null
        }
        else {
            val type: String?
            val markerPath: String?

            if (itemJson.type == null) {
                type = null
                markerPath = null
            }
            else {
                type = itemJson.type!!.type
                markerPath = itemJson.type!!.markerPath
            }

            val structuralObjectsJson = itemJson.structuralObjects

            val structuralObjectsDB =
                structuralObjectsJson?.map {
                    StructuralObjectItemJsonMapper().fromJsonToRoomDB(it)!!.structuralItemsEntityDB }

            val iconsDB =
                structuralObjectsJson?.map {
                    StructuralObjectItemJsonMapper().fromJsonToRoomDB(it)!!.icon }

            return BuildingItemDB(BuildingItemEntityDB(itemJson.id!!,
                    itemJson.inventoryUsrreNumber,
                    itemJson.name,
                    itemJson.isModern.toBoolean(),
                    type,
                    markerPath),
                structuralObjectsDB!!,
                iconsDB!!,
                AddressItemJsonMapper().fromJsonToRoomDB(itemJson.address, itemJson.id)!!
            )
        }
    }

}