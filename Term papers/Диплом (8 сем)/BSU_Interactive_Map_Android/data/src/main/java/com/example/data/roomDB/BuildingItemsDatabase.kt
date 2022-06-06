package com.example.data.roomDB

import androidx.room.Database
import androidx.room.RoomDatabase
import androidx.room.TypeConverters
import com.example.data.roomDB.entities.Converters
import com.example.data.roomDB.entities.buildingItem.BuildingItemDAO
import com.example.data.roomDB.entities.buildingItem.BuildingItemEntityDB
import com.example.data.roomDB.entities.buildingItem.adressItem.AddressItemEntityDB
import com.example.data.roomDB.entities.buildingItem.buildingItemImage.BuildingItemImageEntityDB
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.StructuralObjectItemEntityDB
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem.IconItemEntityDB

@Database(entities = [BuildingItemEntityDB::class, StructuralObjectItemEntityDB::class, BuildingItemImageEntityDB::class,
    AddressItemEntityDB::class, IconItemEntityDB::class], version = 2)
@TypeConverters(Converters::class)
abstract class BuildingItemsDatabase : RoomDatabase() {
    abstract fun buildingItemsDao(): BuildingItemDAO
}