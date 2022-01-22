package com.example.data.roomDB.entities.buildingItem.adressItem

import com.example.data.model.BuildingItemAddressJson

class AddressItemJsonMapper {

    fun fromJsonToRoomDB(itemJson: BuildingItemAddressJson?, buildingItemId: String?) : AddressItemEntityDB?
    {
        if (itemJson == null) {
            return null
        }
        else {
            val latitude: String?
            val longitude: String?

            if (itemJson.coordinates == null) {
                latitude = null
                longitude = null
            }
            else {
                latitude = itemJson.coordinates!!.latitude
                longitude = itemJson.coordinates!!.longitude
            }

            return AddressItemEntityDB(itemJson.id!!,
                buildingItemId,
                itemJson.description,
                latitude,
                longitude)
        }
    }

}
