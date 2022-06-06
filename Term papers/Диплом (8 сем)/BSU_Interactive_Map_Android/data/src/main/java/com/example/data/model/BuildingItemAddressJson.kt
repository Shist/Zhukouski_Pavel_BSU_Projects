package com.example.data.model

import com.google.gson.annotations.SerializedName

data class BuildingItemAddressJson(
    @SerializedName("id") var id: String?,
    @SerializedName("description") var description: String?,
    @SerializedName("coordinates") var coordinates: BuildingItemAddressCoordinatesJson?
)