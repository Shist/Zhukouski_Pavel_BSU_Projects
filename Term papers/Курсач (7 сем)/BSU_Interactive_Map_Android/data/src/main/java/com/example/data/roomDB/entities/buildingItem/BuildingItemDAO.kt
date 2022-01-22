package com.example.data.roomDB.entities.buildingItem

import androidx.room.*
import com.example.data.roomDB.entities.buildingItem.adressItem.AddressItemEntityDB
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.StructuralObjectItemEntityDB
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem.IconItemEntityDB
import kotlinx.coroutines.flow.Flow

@Dao
interface BuildingItemDAO {

    // This operations are needed for entities. We'll use it in more difficult queries
    // =================================
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertBuildingItemEntityDB(buildingItemEntityDB: BuildingItemEntityDB): Long
    @Update
    suspend fun updateBuildingItemEntityDB(buildingItemEntityDB: BuildingItemEntityDB)
    @Delete
    suspend fun deleteBuildingItemEntityDB(buildingItemEntityDB: BuildingItemEntityDB)

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertStructuralObjectItemEntityDB(structuralItemsEntityDB: StructuralObjectItemEntityDB): Long
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertStructuralObjectItemEntitiesListDB(items: List<StructuralObjectItemEntityDB>?): List<Long> {
        val resultValue = emptyList<Long>().toMutableList()
        if (items != null) {
            for (soi: StructuralObjectItemEntityDB in items) {
                resultValue += insertStructuralObjectItemEntityDB(soi)
            }
        }
        return resultValue.toList()
    }
    @Update
    suspend fun updateStructuralObjectItemEntityDB(structuralItemsEntityDB: StructuralObjectItemEntityDB)
    @Update
    suspend fun updateStructuralObjectItemEntitiesListDB(items: List<StructuralObjectItemEntityDB>?) {
        if (items != null) {
            for (soi: StructuralObjectItemEntityDB in items) {
                updateStructuralObjectItemEntityDB(soi)
            }
        }
    }
    @Delete
    suspend fun deleteStructuralObjectItemEntityDB(structuralItemsEntityDB: StructuralObjectItemEntityDB)
    @Delete
    suspend fun deleteStructuralObjectItemEntitiesListDB(items: List<StructuralObjectItemEntityDB>?) {
        if (items != null) {
            for (soi: StructuralObjectItemEntityDB in items) {
                deleteStructuralObjectItemEntityDB(soi)
            }
        }
    }

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertIconItemEntityDB(icon: IconItemEntityDB?): Long
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertIconItemEntitiesListDB(items: List<IconItemEntityDB>?): List<Long> {
        val resultValue = emptyList<Long>().toMutableList()
        if (items != null) {
            for (ii: IconItemEntityDB in items) {
                resultValue += insertIconItemEntityDB(ii)
            }
        }
        return resultValue.toList()
    }
    @Update
    suspend fun updateIconItemEntityDB(icon: IconItemEntityDB?)
    @Update
    suspend fun updateIconItemEntitiesListDB(items: List<IconItemEntityDB>?) {
        if (items != null) {
            for (ii: IconItemEntityDB in items) {
                updateIconItemEntityDB(ii)
            }
        }
    }
    @Delete
    suspend fun deleteIconItemEntityDB(icon: IconItemEntityDB?)
    @Delete
    suspend fun deleteIconItemEntitiesListDB(items: List<IconItemEntityDB>?) {
        if (items != null) {
            for (ii: IconItemEntityDB in items) {
                deleteIconItemEntityDB(ii)
            }
        }
    }

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertAddressItemEntityDB(address: AddressItemEntityDB?): Long
    @Update
    suspend fun updateAddressItemEntityDB(address: AddressItemEntityDB?)
    @Delete
    suspend fun deleteAddressItemEntityDB(address: AddressItemEntityDB?)
    // =================================

    @Transaction
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertOneBuildingItem(item: BuildingItemDB): Long {
        val resultValue = insertBuildingItemEntityDB(item.buildingItemEntityDB)
        insertStructuralObjectItemEntitiesListDB(item.structuralObjectEntities)
        insertIconItemEntitiesListDB(item.iconEntities)
        insertAddressItemEntityDB(item.address)
        return resultValue
    }

    @Transaction
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertBuildingItemsList(items: List<BuildingItemDB>): List<Long> {
        val resultValue = emptyList<Long>().toMutableList()
        for (bi: BuildingItemDB in items) {
            resultValue += insertOneBuildingItem(bi)
        }
        return resultValue
    }

    @Transaction
    @Update
    suspend fun updateOneBuildingItem(item: BuildingItemDB) {
        updateBuildingItemEntityDB(item.buildingItemEntityDB)
        updateStructuralObjectItemEntitiesListDB(item.structuralObjectEntities)
        updateIconItemEntitiesListDB(item.iconEntities)
        updateAddressItemEntityDB(item.address)
    }

    @Transaction
    @Update
    suspend fun updateAllBuildingItems(items: List<BuildingItemDB>) {
        for (bi: BuildingItemDB in items) {
            updateOneBuildingItem(bi)
        }
    }

    @Transaction
    @Delete
    suspend fun deleteOneBuildingItem(item: BuildingItemDB, deleteChildLocations: Boolean) {
        if (deleteChildLocations) {
            deleteStructuralObjectItemEntitiesListDB(item.structuralObjectEntities)
            deleteIconItemEntitiesListDB(item.iconEntities)
            deleteAddressItemEntityDB(item.address)
        }
        deleteBuildingItemEntityDB(item.buildingItemEntityDB)
    }

    @Transaction
    @Delete
    suspend fun deleteAllBuildingItems(items: List<BuildingItemDB>, deleteChildLocations: Boolean) {
        for (bi: BuildingItemDB in items) {
            deleteOneBuildingItem(bi, deleteChildLocations)
        }
    }

    @Transaction
    @Query("SELECT * FROM buildings")
    fun getAllBuildingItems(): Flow<List<BuildingItemDB>>

    @Transaction
    @Query("SELECT * FROM buildings WHERE id = :neededId")
    fun getBuildingItemById(neededId: String): Flow<BuildingItemDB>

}