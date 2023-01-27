package app.technobearproject

import android.content.res.Configuration
import androidx.compose.animation.animateColorAsState
import androidx.compose.animation.animateContentSize
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.Icon
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Surface
import androidx.compose.material.Text
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Info
import androidx.compose.runtime.*
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import app.technobearproject.ui.theme.TechnoBearProjectTheme

object FAQ {

    class Question(val question: String, val answer: String)

    val qList = listOf(
        Question(
            "What is this project about??",
            "Answer:\n" +
                    "TechnoBear is a team of four developers, each of whom actively " +
                    "contributes to the development and promotion of the project. In this " +
                    "application, you have the opportunity to make a purchase of various " +
                    "digital equipment using the interface that we have developed for you. " +
                    "Here is our team:\n"
        ),
        Question(
            "Who are the developers of this application?",
            "Answer:\n" +
                    "Our team consists of the next developers:\n" +
                    "1) Alexey Kokhovets - head of the project\n" +
                    "2) Andrey Grishkin - web component developer\n" +
                    "3) Pavel Zhukovsky - mobile application developer\n" +
                    "4) Fedor Miron - project tester and responsible for the API"
        ),
        Question(
            "Who specifically developed this mobile application?",
            "Answer:\n" +
                    "4-year student of the Faculty of Applied Mathematics and Computer Science " +
                    "from 12 group - Zhukovsky Pavel"
        ),
        Question(
            "Can I use other theme in the application?",
            "Answer:\n" +
                    "Of course. Our application provides you opportunity to use either light " +
                    "or dark theme. Just set light or dark theme at the settings of your" +
                    "android phone and application will automatically adapt to it."
        ),
        Question(
            "Where can I find new items to buy?",
            "Answer:\n" +
                    "You can find a number of items to buy in the \"Catalog\" section."
        ),
        Question(
            "Can I filter any products by the category I need?",
            "Answer:\n" +
                    "Certainly. Our catalog has a category selection function that will help " +
                    "you choose a specific product. There is also a product search function."
        ),
        Question(
            "Why should I create an account?",
            "Answer:\n" +
                    "If you create an account, then you will have the opportunity to enter " +
                    "your personal account and specify data about yourself in advance, so as " +
                    "not to enter them every time you specify the data for placing an order."
        ),
        Question(
            "What can I do if I have not found the answer to my question?",
            "Answer:\n" +
                    "If you still haven't found the answer to your question in this section, " +
                    "you can ask it yourself and send it to us. To do this, go to the " +
                    "\"Contact us\" section and write to us."
        )
    )
}

@Composable
fun FAQ(questions: List<FAQ.Question>) {
    Column {
        Text(text = stringResource(R.string.faq),
            modifier = Modifier.padding(all = 8.dp)
                .fillMaxWidth()
                .background(color = MaterialTheme.colors.onSurface.copy(alpha = 0.1f)),
            fontSize = 48.sp,
            textAlign = TextAlign.Center)
        LazyColumn {
            items(questions) { q ->
                QuestionCard(question = q.question, answer = q.answer)
            }
        }
    }
}

@Composable
@Preview(name = "LightFAQPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkFAQPreview"
)
fun FAQPreview() {
    TechnoBearProjectTheme {
        FAQ(FAQ.qList)
    }
}

@Composable
fun QuestionCard(question: String, answer: String) {
    Row (Modifier.padding(8.dp)) {
        Row(modifier = Modifier.padding(all = 8.dp)) {
            Icon(imageVector = Icons.Default.Info,
                contentDescription = "question",
                modifier = Modifier.size(40.dp))
            Spacer(modifier = Modifier.width(8.dp))

            var isExpanded by rememberSaveable { mutableStateOf(false) }
            val surfaceColor: Color by animateColorAsState(
                if (isExpanded) MaterialTheme.colors.surface else
                    MaterialTheme.colors.surface.copy(alpha = 0.1f),
            )

            Column(modifier = Modifier.clickable { isExpanded = !isExpanded }) {
                Text(
                    text = question,
                    color = MaterialTheme.colors.secondaryVariant,
                    style = MaterialTheme.typography.subtitle2
                )
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
                        text = answer,
                        modifier = Modifier.padding(all = 4.dp),
                        maxLines = if (isExpanded) Int.MAX_VALUE else 1,
                        style = MaterialTheme.typography.body2
                    )
                }
            }
        }
    }
}

@Preview(name = "LightQuestionCardPreview")
@Preview(
    uiMode = Configuration.UI_MODE_NIGHT_YES,
    showBackground = true,
    name = "DarkQuestionCardPreview"
)
@Composable
fun QuestionCardPreview() {
    TechnoBearProjectTheme {
        QuestionCard("Some question", "Some answer")
    }
}
