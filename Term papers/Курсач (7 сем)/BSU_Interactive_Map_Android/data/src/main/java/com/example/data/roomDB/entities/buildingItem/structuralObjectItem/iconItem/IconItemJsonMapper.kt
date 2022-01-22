package com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem

import com.example.data.model.StructuralObjectItemIconJson

class IconItemJsonMapper {

    fun fromJsonToRoomDB(itemJson: StructuralObjectItemIconJson?, structuralObjectItemId: String?,
                         buildingItemId: String?) : IconItemEntityDB?
    {
        return if (itemJson == null) {
            null
        } else {
            IconItemEntityDB(itemJson.structuralObjectId!!,
                structuralObjectItemId,
                itemJson.subdivision,
                itemJson.logoPath,
                buildingItemId)
        }
    }

}
