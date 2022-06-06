package com.example.data.model

import com.google.gson.annotations.SerializedName

data class BuildingItemJson(
    @SerializedName("structuralObjects") val structuralObjects: List<StructuralObjectItemJson?>?,
    @SerializedName("id") var id: String?,
    @SerializedName("inventoryUsrreNumber") var inventoryUsrreNumber: String?,
    @SerializedName("name") var name: String?,
    @SerializedName("isModern") var isModern: String?,
    @SerializedName("address") var address: BuildingItemAddressJson?,
    @SerializedName("type") var type: BuildingItemTypeJson?
)