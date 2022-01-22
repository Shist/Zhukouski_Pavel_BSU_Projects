package app.technobearproject

import android.content.res.Configuration
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material.icons.filled.KeyboardArrowDown
import androidx.compose.material.icons.filled.KeyboardArrowUp
import androidx.compose.material.icons.filled.Search
import androidx.compose.runtime.*
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import app.technobearproject.ui.theme.TechnoBearProjectTheme

@Composable
fun Catalog(isItemSelected: MutableState<Boolean>,
            selectedItem: MutableState<ProductItem>) {
    var search by rememberSaveable { mutableStateOf("") }
    Column {
        Text(text = stringResource(R.string.catalog),
            modifier = Modifier
                .padding(all = 8.dp)
                .fillMaxWidth(),
            fontSize = 36.sp,
            textAlign = TextAlign.Center)
        TextField(
            value = search,
            modifier = Modifier
                .padding(all = 8.dp)
                .fillMaxWidth(),
            onValueChange = {
                search = it
            },
            label = {
                Row {
                    Text("Search")
                    Icon(imageVector = Icons.Default.Search,
                        contentDescription = "search",
                        modifier = Modifier
                            .padding(start = 8.dp))
                }
            },
            maxLines = 1
        )
        LazyColumn {
            val searchedList = itemsWholeList.filter { it.name.contains(search) }
            if (searchedList.isEmpty()) {
                item {
                    Text(text = stringResource(id = R.string.no_items_found),
                        modifier = Modifier.padding(all = 8.dp),
                        fontSize = 48.sp,
                        textAlign = TextAlign.Center)
                }
            } else {
                items(searchedList) { i ->
                    ItemCard(item = i, isItemSelected, selectedItem)
                }
            }
        }
    }
}

@Composable
@Preview(name = "LightCatalogPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkCatalogPreview"
)
fun CatalogPreview() {
    val isItemSelected = rememberSaveable { mutableStateOf(false) }
    val selectedItem = rememberSaveable { mutableStateOf(ProductItem()) }
    TechnoBearProjectTheme {
        Catalog(isItemSelected, selectedItem)
    }
}

@Composable
fun ItemCard(item: ProductItem,
             isItemSelected: MutableState<Boolean>,
             selectedItem: MutableState<ProductItem>) {
    Row(modifier = Modifier
        .padding(all = 8.dp)
        .background(MaterialTheme.colors.primary)
        .clickable {
            isItemSelected.value = true
            selectedItem.value = item
        },
        verticalAlignment = Alignment.CenterVertically) {
        Image(painter = painterResource(item.image),
            contentDescription = "item image",
            modifier = Modifier
                .padding(all = 8.dp))
        Column {
            Text(
                text = item.name,
                modifier = Modifier
                    .padding(all = 8.dp)
            )
            Text(
                text = item.price,
                modifier = Modifier
                    .padding(all = 8.dp)
            )
        }
    }
}

@Preview(name = "LightItemCardPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkItemCardPreview"
)
@Composable
fun ItemCardPreview() {
    val isItemSelected = rememberSaveable { mutableStateOf(false) }
    val selectedItem = rememberSaveable { mutableStateOf(ProductItem()) }
    val itemAmount = rememberSaveable { mutableStateOf("0") }
    TechnoBearProjectTheme {
        ItemCard(item = ProductItem("Name",
            "$100.00",
        R.drawable.qe43q60aauxru_samsung_607d5ce61da8f,
        "Description",
        ProductType.PHONE,
            itemAmount),
        isItemSelected,
        selectedItem)
    }
}

@Composable
fun ItemDetails(isItemSelected: MutableState<Boolean>,
                selectedItem: MutableState<ProductItem>) {
    val oneItemPrice = selectedItem.value.price.substring(1).toFloat()
    val itemsAmount = selectedItem.value.selectedAmount.value.toInt()
    val wholeItemsPrice = "\$${(oneItemPrice * itemsAmount)}"
    var alertDialogNeeded by rememberSaveable { mutableStateOf(false) }
    LazyColumn {
        item {
            Row(modifier = Modifier.clickable {
                isItemSelected.value = false
            } ) {
                Icon(imageVector = Icons.Default.ArrowBack,
                    contentDescription = "back to catalog",
                    modifier = Modifier
                        .padding(all = 8.dp))
                Text(
                    text = stringResource(id = R.string.back_to_catalog),
                    modifier = Modifier
                        .padding(all = 8.dp)
                )
            }
        }
        item {
            Row {
                Column(modifier = Modifier.fillMaxWidth(0.4f)) {
                    Text(
                        text = selectedItem.value.name,
                        modifier = Modifier
                            .padding(all = 8.dp),
                        fontSize = 24.sp,
                        fontWeight = FontWeight.Bold
                    )
                    Image(painter = painterResource(id = selectedItem.value.image),
                        contentDescription = "product image",
                        modifier = Modifier
                            .padding(all = 8.dp))
                }
                Column {
                    Row {
                        Text(
                            text = stringResource(id = R.string.amount),
                            modifier = Modifier
                                .padding(all = 8.dp),
                            fontSize = 24.sp
                        )
                        TextField(
                            value = selectedItem.value.selectedAmount.value,
                            modifier = Modifier
                                .padding(all = 2.dp)
                                .fillParentMaxWidth(0.15f),
                            onValueChange = {
                                selectedItem.value.selectedAmount.value = it
                            },
                            label = { stringResource(id = R.string.amount) },
                            singleLine = true,
                            readOnly = true
                        )
                        Column {
                            Icon(imageVector = Icons.Default.KeyboardArrowUp,
                                contentDescription = "more products",
                                modifier = Modifier
                                    .padding(all = 2.dp)
                                    .clickable {
                                        var temp = selectedItem.value.selectedAmount.value.toInt()
                                        temp += 1
                                        selectedItem.value.selectedAmount.value = temp.toString()
                                    })
                            Icon(imageVector = Icons.Default.KeyboardArrowDown,
                                contentDescription = "less products",
                                modifier = Modifier
                                    .padding(all = 2.dp)
                                    .clickable {
                                        var temp = selectedItem.value.selectedAmount.value.toInt()
                                        temp -= 1
                                        if (temp < 0) temp = 0
                                        selectedItem.value.selectedAmount.value = temp.toString()
                                    })
                        }
                    }
                    Row {
                        Text(
                            text = stringResource(id = R.string.price),
                            modifier = Modifier
                                .padding(all = 8.dp),
                            fontSize = 24.sp
                        )
                        Text(
                            text = wholeItemsPrice,
                            modifier = Modifier
                                .padding(all = 8.dp),
                            fontSize = 24.sp,
                            fontWeight = FontWeight.Bold
                        )
                    }
                    Button(onClick = {
                        if (itemsAmount > 0) {
                            val basketItemsBefore = selectedItem.value.basketAmount.value.toInt()
                            val basketItemsAfter = basketItemsBefore + itemsAmount
                            selectedItem.value.basketAmount.value = basketItemsAfter.toString()
                            alertDialogNeeded = true
                        }
                    },
                        enabled = itemsAmount > 0,
                        modifier = Modifier
                        .padding(all = 8.dp)
                        .fillMaxWidth()
                    ) {
                        Text(text = stringResource(R.string.add_to_basket),
                            modifier = Modifier
                                .padding(all = 8.dp)
                                .fillMaxWidth(),
                            fontSize = 24.sp,
                            textAlign = TextAlign.Center)
                    }
                }
            }
        }
        item {
            Text(
                text = stringResource(R.string.description),
                modifier = Modifier
                    .padding(all = 8.dp),
                fontSize = 24.sp
            )
        }
        item {
            Text(
                text = selectedItem.value.description,
                modifier = Modifier
                    .padding(all = 8.dp),
                fontSize = 18.sp
            )
        }
    }
    if (alertDialogNeeded) {
        AlertDialog(
            onDismissRequest = {
                alertDialogNeeded = false
            },
            title = {
                Text("Success")
            },
            confirmButton = {
                Button(
                    onClick = {
                        alertDialogNeeded = false
                    }
                ) {
                    Text("OK")
                }
            },
            text = {
                Text("Product added to basket successfully:\n" +
                        "Name: ${selectedItem.value.name}\n" +
                        "Price per one: ${selectedItem.value.price}\n" +
                        "Amount: ${selectedItem.value.selectedAmount.value}\n" +
                        "Total price: $wholeItemsPrice")
            },
        )
    }
}

@Preview(name = "LightItemDetailsPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkItemDetailsPreview"
)
@Composable
fun ItemDetailsPreview() {
    val isItemSelected = rememberSaveable { mutableStateOf(false) }
    val itemAmount = rememberSaveable { mutableStateOf("0") }
    val selectedItem = rememberSaveable { mutableStateOf(ProductItem("Name",
        "$100.00",
        R.drawable.qe43q60aauxru_samsung_607d5ce61da8f,
        "Description",
        ProductType.PHONE,
        itemAmount)) }
    TechnoBearProjectTheme {
        ItemDetails(isItemSelected, selectedItem)
    }
}
