package app.technobearproject

import android.content.res.Configuration
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import app.technobearproject.ui.theme.TechnoBearProjectTheme

const val ABOUT_COMPANY = "TechnoBear is a team of four developers, each of whom actively " +
        "contributes to the development and promotion of the project. In this application, " +
        "you have the opportunity to make a purchase of various digital equipment using the " +
        "interface that we have developed for you. Here is our team:\n" +
        "1) Alexey Kokhovets - head of the project\n" +
        "2) Andrey Grishkin - web component developer\n" +
        "3) Pavel Zhukovsky - mobile application developer\n" +
        "4) Fedor Miron - project tester and responsible for the API"

@Composable
fun AboutCompany() {
    LazyColumn {
        item {
            Text(text = stringResource(R.string.about_TechnoBear),
                modifier = Modifier.padding(all = 8.dp),
                fontSize = 48.sp,
                textAlign = TextAlign.Center)
        }
        item {
            Text(text = ABOUT_COMPANY,
                modifier = Modifier.padding(all = 8.dp),
                fontSize = 24.sp,
                textAlign = TextAlign.Start)
        }
    }
}

@Composable
@Preview(name = "LightAboutCompanyPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkAboutCompanyPreview"
)
fun AboutCompanyPreview() {
    TechnoBearProjectTheme {
        AboutCompany()
    }
}