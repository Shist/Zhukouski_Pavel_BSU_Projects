package com.example.data.roomDB.entities.buildingItem.structuralObjectItem

import com.example.data.model.StructuralObjectItemJson
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem.IconItemJsonMapper

// This mapper converts a JSON entity to a database entity
class StructuralObjectItemJsonMapper {

    fun fromJsonToRoomDB(itemJson: StructuralObjectItemJson?) : StructuralObjectItemDB?
    {
        if (itemJson == null) {
            return null
        }
        else {
            val categoryName: String? = if (itemJson.category == null) {
                null
            } else {
                itemJson.category!!.name
            }

            return StructuralObjectItemDB(StructuralObjectItemEntityDB(itemJson.id!!,
                    itemJson.subdivision,
                    itemJson.description,
                    itemJson.website,
                    itemJson.buildingId,
                    categoryName),
                IconItemJsonMapper()
                    .fromJsonToRoomDB(itemJson.icon, itemJson.id, itemJson.buildingId)!!
            )
        }
    }

}