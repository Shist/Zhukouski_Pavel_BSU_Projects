package com.example.domain

data class StructuralObjectItem(

    val id: String,

    val subdivision: String?,

    val description: String?,

    val website: String?,

    val buildingId: String?,

    val category: String?,

    val icon: IconItem?,

)

// This is domain data class. Actually this is copy of corresponding StructuralObjectItemDB, but we
// need it in order to hide the database implementation logic. It is considered good practice
// to have separate classes for the database and classes for the domain.
