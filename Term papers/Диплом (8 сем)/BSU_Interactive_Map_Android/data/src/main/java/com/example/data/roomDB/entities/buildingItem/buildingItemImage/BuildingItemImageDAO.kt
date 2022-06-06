package com.example.data.roomDB.entities.buildingItem.buildingItemImage

import androidx.room.*
import kotlinx.coroutines.flow.Flow

@Dao
interface BuildingItemImageDAO {

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertOneBuildingItemImage(item: BuildingItemImageEntityDB): Long

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertBuildingItemImagesList(items: List<BuildingItemImageEntityDB>): List<Long>

    @Update
    suspend fun updateOneBuildingItemImage(item: BuildingItemImageEntityDB)

    @Update
    suspend fun updateAllBuildingItemImages(items: List<BuildingItemImageEntityDB>)

    @Delete
    suspend fun deleteOneBuildingItemImage(item: BuildingItemImageEntityDB)

    @Delete
    suspend fun deleteAllBuildingItemImages(items: List<BuildingItemImageEntityDB>)

    @Query("SELECT * FROM buildingItemImages")
    fun getAllBuildingItemImages(): Flow<List<BuildingItemImageEntityDB>>

    @Query("SELECT * FROM buildingItemImages WHERE id = :neededId")
    fun getBuildingItemImageById(neededId: String): Flow<BuildingItemImageEntityDB>

}