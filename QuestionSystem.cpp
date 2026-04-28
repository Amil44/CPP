#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

enum Difficulty {
    EASY = 20,
    MEDIUM = 30,
    HARD = 40,
};

class Question {
    char* _QuestionText;
    Difficulty _difficulty;
    vector<int> _answers;
    short _QuestionId;
    short _correctIndex;

public:
    Question() : _QuestionText(nullptr), _difficulty(EASY), _QuestionId(0), _correctIndex(0) {}

    Question(const char* question, Difficulty difficulty, short questionId, vector<int> answers, short correctIndex) {
        _QuestionText = new char[strlen(question) + 1];
        strcpy_s(_QuestionText, strlen(question) + 1, question);
        _difficulty = difficulty;
        _answers = answers;
        _QuestionId = questionId;
        _correctIndex = correctIndex;
    }

    Question(const Question& other) {
        if (other._QuestionText) {
            _QuestionText = new char[strlen(other._QuestionText) + 1];
            strcpy_s(_QuestionText, strlen(other._QuestionText) + 1, other._QuestionText);
        }
        else {
            _QuestionText = nullptr;
        }
        _difficulty = other._difficulty;
        _answers = other._answers;
        _QuestionId = other._QuestionId;
        _correctIndex = other._correctIndex;
    }

    Question& operator=(const Question& other) {
        if (this != &other) {
            delete[] _QuestionText;
            if (other._QuestionText) {
                _QuestionText = new char[strlen(other._QuestionText) + 1];
                strcpy_s(_QuestionText, strlen(other._QuestionText) + 1, other._QuestionText);
            }
            else {
                _QuestionText = nullptr;
            }
            _difficulty = other._difficulty;
            _answers = other._answers;
            _QuestionId = other._QuestionId;
            _correctIndex = other._correctIndex;
        }
        return *this;
    }

    bool operator==(const Question& other) const {
        return _QuestionId == other._QuestionId &&
            _difficulty == other._difficulty &&
            _correctIndex == other._correctIndex &&
            _answers == other._answers &&
            strcmp(_QuestionText, other._QuestionText) ==   0;
    }

    bool operator<(const Question& other) const {
        return _difficulty < other._difficulty;
    }

    char* getQuestionText() const { return _QuestionText; }
    short getId() const { return _QuestionId; }
    Difficulty getDifficulty() const { return _difficulty; }
    int getCorrectAnswer() const { return _answers[_correctIndex]; }

    void printAnswerChoices() const {
        for (int i = 0; i < (int)_answers.size(); i++) {
            cout << "  " << i + 1 << ") " << _answers[i] << "\n";
        }
    }

    static string diff(Difficulty d) {
        switch (d) {
        case EASY: return "EASY";
        case MEDIUM: return "MEDIUM";
        case HARD: return "HARD";
        default: return "Unknown";
        }
    }

    ~Question() {
        delete[] _QuestionText;
    }
};

class Quiz {
    Question* _questionList;
    short _totalQuestions;          
    const int _minPassRating = 51;

public:
    Quiz() : _questionList(nullptr), _totalQuestions(0) {}

    void addQuestion(const Question& quest) {
        Question* temp = new Question[_totalQuestions + 1];
        for (int i = 0; i < _totalQuestions; i++) {
            temp[i] = _questionList[i];
        }
        temp[_totalQuestions] = quest;
        delete[] _questionList;
        _questionList = temp;
        _totalQuestions++;
    }

    void startQuiz() {
        int score = 0;

        cout << "================== QUIZ ==================\n";
        for (int i = 0; i < _totalQuestions; i++) {
            cout << "\n" << i + 1 << ". "
                << _questionList[i].getQuestionText()
                << " (" << Question::diff(_questionList[i].getDifficulty()) << ")\n";

            _questionList[i].printAnswerChoices();

            cout << "Your Answer: ";
            int ans;
            cin >> ans;
             
            if (ans == _questionList[i].getCorrectAnswer()) {
                cout << "Correct!\n";
                score += _questionList[i].getDifficulty();  
            }
            else {
                cout << "Wrong! Correct answer was: "
                    << _questionList[i].getCorrectAnswer() << "\n";
            }
        }
         
        int percentage = (score * 100) / (_totalQuestions * HARD);
        cout << "\n==========================================\n";
        cout << "Your Score: " << score << "\n";
        cout << (percentage >= _minPassRating ? "Result: PASSED" : "Result: FAILED") << "\n";
    }

    void removeQuestion(short id) {
        if (_totalQuestions == 0) return;

        Question* temp = new Question[_totalQuestions - 1];
        int j = 0;
        for (int i = 0; i < _totalQuestions; i++) { 
            if (_questionList[i].getId() != id) {
                temp[j++] = _questionList[i];
            }
        }
        delete[] _questionList;
        _questionList = temp;
        _totalQuestions--;
    }

    ~Quiz() {
        delete[] _questionList;
    }
};

int main() { 
    Question q1("2 + 2 = ?", EASY, 1, { 3,   4,   5,   6,   7 }, 1);
    Question q2("141 + 212 = ?", MEDIUM, 2, { 352, 353, 354, 300, 400 }, 1);
    Question q3("100 * 3 = ?", MEDIUM, 3, { 200, 400, 300, 350, 100 }, 2);
    Question q4("(88+212) * 5 = ?", HARD, 4, { 1000,2000,500, 1500, 750 }, 3);
    Question q5("2^11 = ?", HARD, 5, { 1024,4096,512, 256,  2048 }, 4);

    if (q1 == q2) {
        cout << "Questions are identical\n";
    }
    else {
        cout << "Questions are different\n";
    }

    if (q1 < q2) {
        cout << q1.getQuestionText() << " is easier than " << q2.getQuestionText() << "\n";
    }

    Quiz quiz;
    quiz.addQuestion(q1);
    quiz.addQuestion(q2);
    quiz.addQuestion(q3);
    quiz.addQuestion(q4);
    quiz.addQuestion(q5);
    quiz.removeQuestion(5);

    //quiz.startQuiz();

    return 0;
}