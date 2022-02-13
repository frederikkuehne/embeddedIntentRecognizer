# embeddedIntentRecognizer
This program takes a string input and extracts and returns user intents from it.
Since the application should run on embedded systems, it tries to work with the usage of only the standard libraries and no third party library.
The intent extraction works by relying on predefined keywords and predefined entities.
This method was chosen above e.g. neural networks because normally an intent recognition system converts the user input to be bridged to a predefined application. That application is assumed to provide only a limited amount of functions, thus it itself restricts the number of all keywords and possibly all matching entities.

## Usage
Intents are stored in the file './data/intents' in the form of
```
[intent];[keyword,...];[entity,...]
```
and loaded at runtime. Entity keywords are stored in files with the name of the entity in the folder './data/'.
Call the recognize executable and pass your question as an argument like described in the following:

```
.\recognize "What is the weather like today?"
```

If the program can extract an intent from that input, it will be output in the form of

```
Get [intent] [entities...].
```

## ToDo's
- User inputs like 'Tell me an interesting fact about the weather' will detect the intent 'Get Weather' instead of 'Get Fact', if the 'Get Weather' intent is defined first
- Create a subject-, verb-, object-recognition to recognize non-defined generic inputs