package app.technobearproject

import android.content.res.Configuration
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material.*
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.*
import androidx.compose.runtime.*
import androidx.compose.runtime.saveable.Saver
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import app.technobearproject.ui.theme.TechnoBearProjectTheme
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.launch

enum class MenuPage {
    START_PAGE,
    ACCOUNT,
    CATALOG,
    BASKET,
    ABOUT_COMPANY,
    FAQ,
    CONTACT_US
}

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            TechnoBearProjectTheme {
                MakeScaffold()
            }
        }
    }
}

@Composable
fun MakeScaffold() {
    val scaffoldState = rememberScaffoldState()
    val scope = rememberCoroutineScope()
    val menuPage = rememberSaveable { mutableStateOf(MenuPage.START_PAGE) }
    val isItemSelected = rememberSaveable { mutableStateOf(false) }
    val selectedItem = rememberSaveable { mutableStateOf(ProductItem()) }
    val basketState = rememberSaveable { mutableStateOf(BasketState.BASKET) }
    Scaffold(
        scaffoldState = scaffoldState,
        topBar = {
            TopAppBar(
                navigationIcon = {
                    IconButton(onClick = {
                            if (scaffoldState.drawerState.isClosed) {
                                scope.launch {
                                    scaffoldState.drawerState.open()
                                }
                            }
                            else {
                                scope.launch {
                                    scaffoldState.drawerState.close()
                                }
                            }
                    } ) {
                        Icon(Icons.Filled.Menu, contentDescription = "menu")
                    }
                },
                title = {
                    Text(text = "TechnoBear")
                },
                actions = {
                    // Here we can add some extra button for Toolbar in future
                },
                backgroundColor = MaterialTheme.colors.primarySurface
            )
        },
        drawerContent = {
            MenuContent(scaffoldState, scope, menuPage)
        }
    ) {
        when (menuPage.value) {
            MenuPage.START_PAGE -> {
                InitialInformation()
            }
            MenuPage.ACCOUNT -> {
                Account()
            }
            MenuPage.CATALOG -> {
                if (isItemSelected.value) {
                    ItemDetails(isItemSelected, selectedItem)
                } else {
                    Catalog(isItemSelected, selectedItem)
                }
            }
            MenuPage.BASKET -> {
                when (basketState.value) {
                    BasketState.BASKET -> {
                        Basket(basketState)
                    }
                    BasketState.CHECKOUT_ORDER -> {
                        CheckoutOrder(basketState)
                    }
                    BasketState.DELIVERY_DETAILS -> {
                        DeliveryDetails(basketState, menuPage, isItemSelected)
                    }
                }
            }
            MenuPage.ABOUT_COMPANY -> {
                AboutCompany()
            }
            MenuPage.FAQ -> {
                FAQ(FAQ.qList)
            }
            MenuPage.CONTACT_US -> {
                ContactUs()
            }
        }
    }
}

@Composable
@Preview(name = "LightScaffoldPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkScaffoldPreview"
)
fun MakeScaffoldPreview() {
    TechnoBearProjectTheme {
        MakeScaffold()
    }
}

@Composable
fun MenuContent(scaffoldState: ScaffoldState,
                scope: CoroutineScope,
                menuPage: MutableState<MenuPage>) {
    LazyColumn(modifier = Modifier
        .padding(all = 8.dp)
        .fillMaxSize(),
        verticalArrangement = Arrangement.Top,
        horizontalAlignment = Alignment.Start) {
        item {
            Row(modifier = Modifier.padding(all = 8.dp)) {
                Text(text = stringResource(id = R.string.menu_name),
                    fontSize = 48.sp,
                    modifier = Modifier.padding(all = 8.dp))
            }
        }
        item {
            Row(verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier
                    .padding(all = 8.dp)
                    .fillMaxWidth()
                    .clickable {
                        menuPage.value = MenuPage.ACCOUNT
                        scope.launch {
                            scaffoldState.drawerState.close()
                        }
                    } ) {
                Icon(imageVector = Icons.Default.AccountBox,
                    contentDescription = stringResource(id = R.string.account),
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .defaultMinSize(48.dp, 48.dp))
                Text(text = stringResource(id = R.string.account),
                    fontSize = 24.sp,
                    modifier = Modifier.padding(all = 8.dp))
            }
        }
        item {
            Row(verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier
                    .padding(all = 8.dp)
                    .fillMaxWidth()
                    .clickable {
                        menuPage.value = MenuPage.CATALOG
                        scope.launch {
                            scaffoldState.drawerState.close()
                        }
                    } ) {
                Icon(imageVector = Icons.Default.Search,
                    contentDescription = stringResource(id = R.string.catalog),
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .defaultMinSize(48.dp, 48.dp))
                Text(text = stringResource(id = R.string.catalog),
                    fontSize = 24.sp,
                    modifier = Modifier.padding(all = 8.dp))
            }
        }
        item {
            Row(verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier
                    .padding(all = 8.dp)
                    .fillMaxWidth()
                    .clickable {
                        menuPage.value = MenuPage.BASKET
                        scope.launch {
                            scaffoldState.drawerState.close()
                        }
                    } ) {
                Icon(imageVector = Icons.Default.ShoppingCart,
                    contentDescription = stringResource(id = R.string.basket),
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .defaultMinSize(48.dp, 48.dp))
                Text(text = stringResource(id = R.string.basket),
                    fontSize = 24.sp,
                    modifier = Modifier.padding(all = 8.dp))
            }
        }
        item {
            Row(verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier
                    .padding(all = 8.dp)
                    .fillMaxWidth()
                    .clickable {
                        menuPage.value = MenuPage.ABOUT_COMPANY
                        scope.launch {
                            scaffoldState.drawerState.close()
                        }
                    } ) {
                Icon(imageVector = Icons.Default.Info,
                    contentDescription = stringResource(id = R.string.about_company),
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .defaultMinSize(48.dp, 48.dp))
                Text(text = stringResource(id = R.string.about_company),
                    fontSize = 24.sp,
                    modifier = Modifier.padding(all = 8.dp))
            }
        }
        item {
            Row(verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier
                    .padding(all = 8.dp)
                    .fillMaxWidth()
                    .clickable {
                        menuPage.value = MenuPage.FAQ
                        scope.launch {
                            scaffoldState.drawerState.close()
                        }
                    } ) {
                Icon(imageVector = Icons.Default.List,
                    contentDescription = stringResource(id = R.string.faq),
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .defaultMinSize(48.dp, 48.dp))
                Text(text = stringResource(id = R.string.faq),
                    fontSize = 24.sp,
                    modifier = Modifier.padding(all = 8.dp))
            }
        }
        item {
            Row(verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier
                    .padding(all = 8.dp)
                    .fillMaxWidth()
                    .clickable {
                        menuPage.value = MenuPage.CONTACT_US
                        scope.launch {
                            scaffoldState.drawerState.close()
                        }
                    } ) {
                Icon(imageVector = Icons.Default.Email,
                    contentDescription = stringResource(id = R.string.contact_us),
                    modifier = Modifier
                        .padding(all = 8.dp)
                        .defaultMinSize(48.dp, 48.dp))
                Text(text = stringResource(id = R.string.contact_us),
                    fontSize = 24.sp,
                    modifier = Modifier.padding(all = 8.dp))
            }
        }
    }
}

@Composable
@Preview(name = "LightMenuContentPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkMenuContentPreview"
)
fun MenuContentPreview() {
    TechnoBearProjectTheme {
        val scaffoldState = rememberScaffoldState()
        val scope = rememberCoroutineScope()
        val menuPage = rememberSaveable { mutableStateOf(MenuPage.START_PAGE) }
        MenuContent(scaffoldState, scope, menuPage)
    }
}
