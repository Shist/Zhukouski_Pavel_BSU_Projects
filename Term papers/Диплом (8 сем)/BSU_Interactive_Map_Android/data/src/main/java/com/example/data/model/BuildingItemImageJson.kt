package com.example.data.model

import com.google.gson.annotations.SerializedName

data class BuildingItemImageJson (
    @SerializedName("buildingId") val buildingId: String?,
    @SerializedName("imagePath") var imagePath: String?,
    @SerializedName("description") var description: String?
)