package com.example.domain

data class BuildingItem(

    val id: String,

    val structuralObjects: List<StructuralObjectItem?>?,

    val inventoryUsrreNumber: String?,

    val name: String?,

    val isModern: Boolean?,

    val address: AddressItem?,

    val type: String?,

    val markerPath: String?

)

// This is domain data class. Actually this is copy of corresponding BuildingItemDB, but we
// need it in order to hide the database implementation logic. It is considered good practice
// to have separate classes for the database and classes for the domain.
