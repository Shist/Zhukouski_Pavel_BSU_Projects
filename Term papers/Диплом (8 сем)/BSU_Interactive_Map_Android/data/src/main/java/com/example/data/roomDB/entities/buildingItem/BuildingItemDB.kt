package com.example.data.roomDB.entities.buildingItem

import androidx.room.Embedded
import androidx.room.Relation
import com.example.data.roomDB.entities.buildingItem.adressItem.AddressItemEntityDB
import com.example.data.roomDB.entities.buildingItem.buildingItemImage.BuildingItemImageEntityDB
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.StructuralObjectItemEntityDB
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem.IconItemEntityDB

data class BuildingItemDB (

    // This class is needed for getItems() method in BuildingItemDAO
    // This is a combination of:
    // 1) AddressItemEntityDB table
    // 2) StructuralObjectItemEntityDB table
    // 3) BuildingItemImageEntityDB table
    // 4) IconItemEntityDB table
    // This class can only be used in SELECT queries, not in INSERT, UPDATE, DELETE

    @Embedded
    val buildingItemEntityDB: BuildingItemEntityDB,

    @Relation(
        parentColumn = "id",
        entityColumn = "buildingItemId"
    )
    val structuralObjectEntities: List<StructuralObjectItemEntityDB>?,

    @Relation(
        parentColumn = "id",
        entityColumn = "buildingItemId"
    )
    val buildingItemImageEntities: List<BuildingItemImageEntityDB>?,

    @Relation(
        parentColumn = "id",
        entityColumn = "buildingItemId"
    )
    val iconEntities: List<IconItemEntityDB>?,

    @Relation(
        parentColumn = "id",
        entityColumn = "buildingItemId"
    )
    val address: AddressItemEntityDB?

)