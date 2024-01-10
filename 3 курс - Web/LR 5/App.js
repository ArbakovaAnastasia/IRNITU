import "./App.css";
import React, { useState } from "react";

function App() {
  const questions = [
    {
      questionText: "Что является языком программирования?",
      answerOptions: [
        { answerText: "Windows", isCorrect: false },
        { answerText: "JavaScript", isCorrect: true },
        { answerText: "C--", isCorrect: false },
        { answerText: "GoGo", isCorrect: false }
      ]
    },
    {
      questionText: "Что не является циклом?",
      answerOptions: [
        { answerText: "while", isCorrect: false },
        { answerText: "for", isCorrect: false },
        { answerText: "do...while", isCorrect: false },
        { answerText: "if", isCorrect: true }
      ]
    },
    {
      questionText: "Операция вычитания?",
      answerOptions: [
        { answerText: "+", isCorrect: false },
        { answerText: "-", isCorrect: true },
        { answerText: "/", isCorrect: false },
        { answerText: "*", isCorrect: false }
      ]
    },
    {
      questionText: "Какой оператор прибавляет к числу единицу?",
      answerOptions: [
        { answerText: "--", isCorrect: false },
        { answerText: "//", isCorrect: false },
        { answerText: "++", isCorrect: true },
        { answerText: "**", isCorrect: false }
      ]
    }
  ];

  const [currentQuestion, setCurrentQuestion] = useState(0);
  const [score, setScore] = useState(0);
  const [showScore, setShowScore] = useState(false);
  const handleAnswerOptionClick = (isCorrect) => {
    if (isCorrect) {
      setScore(score + 1);
    }
    const nextQuestion = currentQuestion + 1;
    if (nextQuestion < questions.length) {
      setCurrentQuestion(nextQuestion);
    } else {
      setShowScore(true);
    }
  };

  const refresh = () => {
    setCurrentQuestion(0);
    setScore(0);
    setShowScore(false);
  };

  return (
    <div className="body">
      <div className="app">
        {showScore ? (
          <div className="section__score">
            <div>
              Правильных ответов {score} из {questions.length}
            </div>
            <button className="refresh_btn" onClick={refresh}>
              Попробовать еще раз
            </button>
          </div>
        ) : (
          <div className="quizz">
            <div className="question__section">
              <div className="question__count">
                <span>Вопрос {currentQuestion + 1}</span> / {questions.length}
              </div>
              <div className="question__text">
                {questions[currentQuestion].questionText}
              </div>
            </div>
            <div className="answer__section">
              {questions[currentQuestion].answerOptions.map((item) => (
                <button onClick={() => handleAnswerOptionClick(item.isCorrect)}>
                  {item.answerText}
                </button>
              ))}
            </div>
          </div>
        )}
      </div>
    </div>
  );
}

export default App;
