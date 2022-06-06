package com.example.domain

import kotlinx.coroutines.flow.Flow

// This is interface for repository, here you should declare all needed methods and functions
interface DataRepository {

    suspend fun loadData()

    fun getItems(): Flow<List<BuildingItem>>

}