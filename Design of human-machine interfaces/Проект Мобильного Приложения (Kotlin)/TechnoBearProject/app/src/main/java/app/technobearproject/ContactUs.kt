package app.technobearproject

import android.content.res.Configuration
import androidx.compose.foundation.layout.*
import androidx.compose.material.AlertDialog
import androidx.compose.material.Button
import androidx.compose.material.Text
import androidx.compose.material.TextField
import androidx.compose.runtime.*
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import app.technobearproject.ui.theme.TechnoBearProjectTheme

@Composable
fun ContactUs() {
    var mail by rememberSaveable { mutableStateOf("") }
    var feedback by rememberSaveable { mutableStateOf("") }
    var alertDialogNeeded by rememberSaveable { mutableStateOf(false) }
    var alertDialogTitle by rememberSaveable { mutableStateOf("Error") }
    var alertDialogMessage by rememberSaveable { mutableStateOf("Something get wrong...") }
    Column {
        Text(text = stringResource(R.string.contact_us),
            modifier = Modifier
                .padding(all = 8.dp)
                .fillMaxWidth(),
            fontSize = 48.sp,
            textAlign = TextAlign.Center)
        TextField(
            value = mail,
            modifier = Modifier
                .padding(all = 8.dp)
                .fillMaxWidth(),
            onValueChange = {
                mail = it
            },
            label = { Text("Enter your mail here:") },
            maxLines = 1
        )
        TextField(
            value = feedback,
            modifier = Modifier
                .padding(all = 8.dp)
                .fillMaxWidth()
                .weight(1f),
            onValueChange = {
                feedback = it
            },
            label = { Text("Write here your question or feedback:") }
        )
        Button(onClick = {
            alertDialogNeeded = true
            if (mail.isNotEmpty() and mail.contains('@')) {
                if (feedback.isNotEmpty()) {
                    alertDialogTitle = "Success"
                    alertDialogMessage = "Your feedback has been sent to $mail, we will contact you soon."
                    mail = ""
                    feedback = ""
                } else {
                    alertDialogTitle = "Error"
                    alertDialogMessage = "Your feedback is empty. Enter some information, please..."
                }
            } else {
                alertDialogTitle = "Error"
                alertDialogMessage = "Entered mail is empty or incorrect. Please, try to enter correct mail..."
            }
        }, modifier = Modifier
            .padding(all = 8.dp)
            .fillMaxWidth()
        ) {
            Text(text = stringResource(R.string.send_feedback),
                modifier = Modifier
                    .padding(all = 8.dp)
                    .fillMaxWidth(),
                fontSize = 24.sp,
                textAlign = TextAlign.Center)
        }
    }
    if (alertDialogNeeded) {
        AlertDialog(
            onDismissRequest = {
                alertDialogNeeded = false
            },
            title = {
                Text(alertDialogTitle)
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
                Text(alertDialogMessage)
            },
        )
    }
}

@Composable
@Preview(name = "LightContactUsPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkContactUsPreview"
)
fun ContactUsPreview() {
    TechnoBearProjectTheme {
        ContactUs()
    }
}