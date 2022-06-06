package com.example.data.repository.mappers

import com.example.data.roomDB.entities.buildingItem.adressItem.AddressItemEntityDB
import com.example.domain.AddressItem

// This mapper converts a database entity to a domain entity
class AddressItemDBMapper {

    fun fromDBToDomain(item: AddressItemEntityDB?) : AddressItem? {
        return if (item == null) {
            null
        } else {
            AddressItem(item.id,
                item.description,
                item.latitude,
                item.longitude)
        }
    }

}