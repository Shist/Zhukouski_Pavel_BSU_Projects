package app.technobearproject

import android.content.res.Configuration
import androidx.compose.animation.animateColorAsState
import androidx.compose.animation.animateContentSize
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.*
import androidx.compose.runtime.*
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import app.technobearproject.ui.theme.TechnoBearProjectTheme
import kotlin.math.round

enum class BasketState {
    BASKET,
    CHECKOUT_ORDER,
    DELIVERY_DETAILS
}

fun Double.round(decimals: Int): Double {
    var multiplier = 1.0
    repeat(decimals) { multiplier *= 10 }
    return round(this * multiplier) / multiplier
}

@Composable
fun Basket(basketState: MutableState<BasketState>) {
    var search by rememberSaveable { mutableStateOf("") }
    val basketList = itemsWholeList.filter { it.basketAmount.value.toInt() > 0 }
    Column {
        Text(text = stringResource(R.string.basket),
            modifier = Modifier
                .padding(all = 8.dp)
                .fillMaxWidth(),
            fontSize = 36.sp,
            textAlign = TextAlign.Center)
        if (basketList.isNotEmpty()) {
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
            LazyColumn(modifier = Modifier.weight(1f)) {
                val searchedList = basketList.filter { it.name.contains(search) }
                if (searchedList.isEmpty()) {
                    item {
                        Text(text = stringResource(id = R.string.no_items_found),
                            modifier = Modifier.padding(all = 8.dp),
                            fontSize = 48.sp,
                            textAlign = TextAlign.Center)
                    }
                } else {
                    items(searchedList) { i ->
                        BasketItemCard(item = i)
                    }
                }
            }
            Button(onClick = {
                basketState.value = BasketState.CHECKOUT_ORDER
            }, modifier = Modifier
                .padding(all = 8.dp)
                .fillMaxWidth()
            ) {
                Text(text = stringResource(R.string.checkout_order),
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .fillMaxWidth(),
                    fontSize = 24.sp,
                    textAlign = TextAlign.Center)
            }
        } else {
            Text(text = stringResource(id = R.string.basket_is_empty),
            modifier = Modifier.padding(all = 8.dp),
            fontSize = 48.sp,
            textAlign = TextAlign.Center)
        }
    }
}

@Composable
@Preview(name = "LightBasketPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkBasketPreview"
)
fun BasketPreview() {
    val basketState = rememberSaveable { mutableStateOf(BasketState.BASKET) }
    TechnoBearProjectTheme {
        Basket(basketState)
    }
}

@Composable
fun BasketItemCard(item: ProductItem) {
    val oneItemPrice = item.price.substring(1).toFloat()
    val itemsAmount = item.basketAmount.value.toInt()
    val wholeItemsPrice = "\$${(oneItemPrice * itemsAmount)}"
    Row(modifier = Modifier
        .padding(all = 8.dp)
        .background(MaterialTheme.colors.primary),
        verticalAlignment = Alignment.CenterVertically) {
        Image(painter = painterResource(item.image),
            contentDescription = "item image",
            modifier = Modifier
                .padding(all = 8.dp)
                .fillMaxWidth(0.3f))
        Column {
            Row {
                Text(
                    text = item.name,
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .fillMaxWidth(0.8f)
                )
                Icon(imageVector = Icons.Filled.Close,
                    contentDescription = "delete good from basket",
                    modifier = Modifier
                        .size(40.dp)
                        .clickable {
                            item.basketAmount.value = "0"
                        })
            }
            Row(horizontalArrangement = Arrangement.Center,
                verticalAlignment = Alignment.CenterVertically) {
                Row(horizontalArrangement = Arrangement.Center,
                verticalAlignment = Alignment.CenterVertically) {
                    Text(
                        text = stringResource(id = R.string.amount),
                        modifier = Modifier
                            .padding(all = 8.dp),
                    )
                    TextField(
                        value = item.basketAmount.value,
                        modifier = Modifier
                            .padding(all = 8.dp)
                            .fillMaxWidth(0.3f),
                        onValueChange = {
                            item.basketAmount.value = it
                        },
                        label = { stringResource(id = R.string.amount) },
                        singleLine = true,
                        readOnly = true
                    )
                    Column {
                        Icon(imageVector = Icons.Default.KeyboardArrowUp,
                            contentDescription = "more products",
                            modifier = Modifier
                                .padding(all = 8.dp)
                                .clickable {
                                    var temp = item.basketAmount.value.toInt()
                                    temp += 1
                                    item.basketAmount.value = temp.toString()
                                })
                        Icon(imageVector = Icons.Default.KeyboardArrowDown,
                            contentDescription = "less products",
                            modifier = Modifier
                                .padding(all = 8.dp)
                                .clickable {
                                    var temp = item.basketAmount.value.toInt()
                                    temp -= 1
                                    if (temp < 0) temp = 0
                                    item.basketAmount.value = temp.toString()
                                })
                    }
                }
                Text(
                    text = wholeItemsPrice,
                    modifier = Modifier
                        .padding(all = 8.dp),
                    fontWeight = FontWeight.Bold
                )
            }
        }
    }
}

@Preview(name = "LightBasketItemCardPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkBasketItemCardPreview"
)
@Composable
fun BasketItemCardPreview() {
    val itemAmount = rememberSaveable { mutableStateOf("1") }
    val currItem = rememberSaveable { mutableStateOf(ProductItem("Name",
        "$100.00",
        R.drawable.qe43q60aauxru_samsung_607d5ce61da8f,
        "Description",
        ProductType.PHONE,
        itemAmount)) }
    TechnoBearProjectTheme {
        BasketItemCard(currItem.value)
    }
}

@Composable
fun CheckoutOrder(basketState: MutableState<BasketState>) {
    var phoneNumber by rememberSaveable { mutableStateOf("") }
    var alertDialogNeeded by rememberSaveable { mutableStateOf(false) }
    val basketList = itemsWholeList.filter { it.basketAmount.value.toInt() > 0 }
    var descriptionDetails = "Tap here to open order details\n"
    descriptionDetails += "====================\n"
    var totalSum = 0.0
    for (item in basketList) {
        descriptionDetails += "Product: " + item.name + "\n"
        descriptionDetails += "Price per One: " + item.price + "\n"
        descriptionDetails += "Amount: " + item.basketAmount.value + "\n"
        val currSum = item.price.substring(1).toFloat() * item.basketAmount.value.toInt()
        totalSum += currSum
        descriptionDetails += "Total Product Price: \$" + (currSum).toString() + "\n"
        descriptionDetails += "====================\n"
    }
    Column {
        LazyColumn(modifier = Modifier.weight(1f)) {
            item {
                Row(modifier = Modifier.clickable {
                    basketState.value = BasketState.BASKET
                } ) {
                    Icon(imageVector = Icons.Default.ArrowBack,
                        contentDescription = "back to basket",
                        modifier = Modifier
                            .padding(all = 8.dp))
                    Text(
                        text = stringResource(id = R.string.back_to_basket),
                        modifier = Modifier
                            .padding(all = 8.dp)
                    )
                }
            }
            item {
                Text(text = stringResource(R.string.checkout_order),
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .fillMaxWidth(),
                    fontSize = 36.sp,
                    textAlign = TextAlign.Center)
            }
            item {
                TextField(
                    value = phoneNumber,
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .fillMaxWidth(),
                    onValueChange = {
                        phoneNumber = it
                    },
                    label = {
                        Row {
                            Text("Enter your phone number:")
                            Icon(imageVector = Icons.Default.Phone,
                                contentDescription = "phone number",
                                modifier = Modifier
                                    .padding(start = 8.dp))
                        }
                    },
                    maxLines = 1
                )
            }
            item {
                Row (Modifier.padding(8.dp)) {
                    Row(modifier = Modifier.padding(all = 8.dp)) {
                        var isExpanded by rememberSaveable { mutableStateOf(false) }
                        val surfaceColor: Color by animateColorAsState(
                            if (isExpanded) MaterialTheme.colors.surface else
                                MaterialTheme.colors.surface.copy(alpha = 0.1f),
                        )
                        Column(modifier = Modifier.clickable { isExpanded = !isExpanded }) {
                            Text(text = stringResource(R.string.order_details),
                                modifier = Modifier
                                    .padding(all = 8.dp)
                                    .fillMaxWidth(),
                                fontSize = 32.sp,
                                textAlign = TextAlign.Start)
                            Spacer(modifier = Modifier.height(4.dp))
                            Surface(
                                shape = MaterialTheme.shapes.medium,
                                elevation = 1.dp,
                                color = surfaceColor,
                                modifier = Modifier
                                    .animateContentSize()
                                    .padding(1.dp)
                            ) {
                                Text(
                                    text = descriptionDetails,
                                    modifier = Modifier.padding(all = 4.dp),
                                    maxLines = if (isExpanded) Int.MAX_VALUE else 1,
                                    style = MaterialTheme.typography.body2
                                )
                            }
                        }
                    }
                }
            }
            item {
                Row(Modifier.padding(8.dp)) {
                    Text(text = stringResource(R.string.total_price),
                        modifier = Modifier
                            .padding(all = 8.dp)
                            .fillMaxWidth(0.5f),
                        fontSize = 32.sp,
                        textAlign = TextAlign.Start)
                    Text(text = "\$${totalSum.round(2)}",
                        modifier = Modifier
                            .padding(all = 8.dp)
                            .fillMaxWidth(),
                        fontSize = 32.sp,
                        textAlign = TextAlign.Start)
                }
            }
        }
        Button(onClick = {
            if (phoneNumber.isEmpty()) {
                alertDialogNeeded = true
            } else {
                basketState.value = BasketState.DELIVERY_DETAILS
            }
        }, modifier = Modifier
            .padding(all = 8.dp)
            .fillMaxWidth()
        ) {
            Text(text = stringResource(R.string.delivery_details),
                modifier = Modifier
                    .padding(all = 8.dp)
                    .fillMaxWidth(),
                fontSize = 24.sp,
                textAlign = TextAlign.Center)
        }
        if (alertDialogNeeded) {
            AlertDialog(
                onDismissRequest = {
                    alertDialogNeeded = false
                },
                title = {
                    Text("Error")
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
                    Text(stringResource(id = R.string.empty_phone_number))
                },
            )
        }
    }
}

@Composable
@Preview(name = "LightCheckoutOrderPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkCheckoutOrderPreview"
)
fun CheckoutOrderPreview() {
    val basketState = rememberSaveable { mutableStateOf(BasketState.CHECKOUT_ORDER) }
    TechnoBearProjectTheme {
        CheckoutOrder(basketState)
    }
}

@Composable
fun DeliveryDetails(basketState: MutableState<BasketState>,
                    menuState: MutableState<MenuPage>,
                    isItemSelected: MutableState<Boolean>) {
    val radioOptions = listOf(stringResource(id = R.string.pick_up_point),
        stringResource(id = R.string.home_delivery))
    val selectedButton = rememberSaveable { mutableStateOf(radioOptions[0]) }
    var alertDialogNeeded by rememberSaveable { mutableStateOf(false) }
    var alertDialogTitle by rememberSaveable { mutableStateOf("Error") }
    var alertDialogMessage by rememberSaveable { mutableStateOf("Something get wrong...") }
    val deliveryOptions = listOf("Dzerzhinskaga, 122", "Slobodskaya, 177", "Independence, 4")
    var expanded by rememberSaveable { mutableStateOf(false) }
    var selectedIndex by rememberSaveable { mutableStateOf(0) }
    var addressInfo by rememberSaveable { mutableStateOf("") }
    Column {
        LazyColumn(modifier = Modifier.weight(1f)) {
            item {
                Row(modifier = Modifier.clickable {
                    basketState.value = BasketState.CHECKOUT_ORDER
                }) {
                    Icon(
                        imageVector = Icons.Default.ArrowBack,
                        contentDescription = "back to checkout order",
                        modifier = Modifier
                            .padding(all = 8.dp)
                    )
                    Text(
                        text = stringResource(id = R.string.back_to_checkout_order),
                        modifier = Modifier
                            .padding(all = 8.dp)
                    )
                }
            }
            item {
                Text(
                    text = stringResource(R.string.delivery_details),
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .fillMaxWidth(),
                    fontSize = 36.sp,
                    textAlign = TextAlign.Center
                )
            }
            item {
                Text(
                    text = stringResource(R.string.choose_delivery),
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .fillMaxWidth(),
                    fontSize = 28.sp,
                    textAlign = TextAlign.Center
                )
            }
            item {
                Column {
                    Row(verticalAlignment = Alignment.CenterVertically,
                        modifier = Modifier
                            .background(MaterialTheme.colors.onSurface.copy(alpha = 0.1f))
                            .fillMaxWidth()
                            .clickable {
                                selectedButton.value = radioOptions[0]
                            }) {
                        RadioButton(
                            selected = selectedButton.value == radioOptions[0],
                            modifier = Modifier.padding(all = 8.dp),
                            onClick = {
                                selectedButton.value = radioOptions[0]
                            }
                        )
                        Text(
                            text = radioOptions[0],
                            modifier = Modifier.padding(all = 8.dp),
                            fontSize = 32.sp
                        )
                    }
                    Row(verticalAlignment = Alignment.CenterVertically,
                        modifier = Modifier
                            .background(MaterialTheme.colors.onSurface.copy(alpha = 0.1f))
                            .fillMaxWidth()
                            .clickable {
                                selectedButton.value = radioOptions[1]
                            }) {
                        RadioButton(
                            selected = selectedButton.value == radioOptions[1],
                            modifier = Modifier.padding(all = 8.dp),
                            onClick = {
                                selectedButton.value = radioOptions[1]
                            }
                        )
                        Text(
                            text = radioOptions[1],
                            modifier = Modifier.padding(all = 8.dp),
                            fontSize = 32.sp
                        )
                    }
                    when (selectedButton.value) {
                        radioOptions[0] -> {
                            Row(verticalAlignment = Alignment.CenterVertically,
                                modifier = Modifier
                                    .fillMaxWidth()) {
                                Text(
                                    text = stringResource(R.string.choose_pick_up),
                                    modifier = Modifier
                                        .padding(all = 8.dp)
                                        .fillMaxWidth(),
                                    fontSize = 28.sp,
                                    textAlign = TextAlign.Center
                                )
                            }
                            Row(verticalAlignment = Alignment.CenterVertically,
                                modifier = Modifier.fillMaxWidth()) {
                                Box(modifier = Modifier
                                    .background(MaterialTheme.colors.onSurface.copy(alpha = 0.1f))
                                    .fillMaxSize()
                                    .padding(all = 8.dp)) {
                                    Text(
                                        deliveryOptions[selectedIndex],
                                        fontSize = 32.sp,
                                        modifier = Modifier
                                            .fillMaxWidth()
                                            .clickable(onClick = { expanded = true })
                                    )
                                    DropdownMenu(
                                        expanded = expanded,
                                        onDismissRequest = {
                                            expanded = false
                                        },
                                        modifier = Modifier
                                            .fillMaxWidth()
                                            .background(MaterialTheme.colors.surface)
                                    ) {
                                        deliveryOptions.forEachIndexed { index, title ->
                                            DropdownMenuItem(
                                                onClick = {
                                                    selectedIndex = index
                                                    expanded = false
                                                }) {
                                                Text(text = title)
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        radioOptions[1] -> {
                            Row(verticalAlignment = Alignment.CenterVertically,
                                modifier = Modifier
                                    .fillMaxWidth()) {
                                Text(
                                    text = stringResource(R.string.enter_address),
                                    modifier = Modifier
                                        .padding(all = 8.dp)
                                        .fillMaxWidth(),
                                    fontSize = 28.sp,
                                    textAlign = TextAlign.Center
                                )
                            }
                            Row(verticalAlignment = Alignment.CenterVertically,
                                modifier = Modifier.fillMaxWidth()) {
                                TextField(
                                    value = addressInfo,
                                    modifier = Modifier
                                        .padding(all = 8.dp)
                                        .fillMaxWidth(),
                                    onValueChange = {
                                        addressInfo = it
                                    },
                                    label = { Text("Write here your address and other information:") }
                                )
                            }
                        }
                    }
                }
            }
        }
        Button(onClick = {
            alertDialogNeeded = true
            if (selectedButton.value == radioOptions[1] && addressInfo.isEmpty()) {
                alertDialogTitle = "Error"
                alertDialogMessage = "You selected home delivery, but did not provide an " +
                        "address. Specify the address or select a pick-up method."
            } else {
                alertDialogTitle = "Success"
                alertDialogMessage = "Thank you for your purchase! Our staff will contact " +
                        "you regarding your order as soon as possible."
            }
        }, modifier = Modifier
            .padding(all = 8.dp)
            .fillMaxWidth()
        ) {
            Text(text = stringResource(R.string.complete_order),
                modifier = Modifier
                    .padding(all = 8.dp)
                    .fillMaxWidth(),
                fontSize = 24.sp,
                textAlign = TextAlign.Center)
        }
        if (alertDialogNeeded) {
            AlertDialog(
                onDismissRequest = {
                    alertDialogNeeded = false
                    if (alertDialogTitle == "Success") {
                        for (item in itemsWholeList) {
                            item.basketAmount.value = "0"
                        }
                        basketState.value = BasketState.BASKET
                        menuState.value = MenuPage.CATALOG
                        isItemSelected.value = false
                    }
                },
                title = {
                    Text(alertDialogTitle)
                },
                confirmButton = {
                    Button(
                        onClick = {
                            alertDialogNeeded = false
                            if (alertDialogTitle == "Success") {
                                for (item in itemsWholeList) {
                                    item.basketAmount.value = "0"
                                }
                                basketState.value = BasketState.BASKET
                                menuState.value = MenuPage.CATALOG
                                isItemSelected.value = false
                            }
                        }
                    ) {
                        Text("OK")
                    }
                },
                text = {
                    Text(alertDialogMessage)
                },
            )
        }
    }
}

@Composable
@Preview(name = "LightDeliveryDetailsPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkDeliveryDetailsPreview"
)
fun DeliveryDetailsPreview() {
    val basketState = rememberSaveable { mutableStateOf(BasketState.DELIVERY_DETAILS) }
    val menuState = rememberSaveable { mutableStateOf(MenuPage.BASKET) }
    val isItemSelected = rememberSaveable { mutableStateOf(false) }
    TechnoBearProjectTheme {
        DeliveryDetails(basketState, menuState, isItemSelected)
    }
}
