public class Toyota extends Car {
    private boolean isRaceCar;

    public Toyota(String number, String color, String model, boolean isRaceCar) {
        super(number, color, model); //супер конструктор, который уже находится в абстрактном классе
        this.isRaceCar = isRaceCar;
    }
    public void startRace(){
        if (this.isRaceCar)
            System.out.println("Врум-врум, гонка началась!");
        else
            System.out.println("Я не люблю гонки((");
    }
    @Override
    public String toString() {
        String[] classInfo = this.getClass().toString().split(" ");
        return classInfo[1]+ " (Номер: "+this.getNumber()+", цвет: "+this.getColor()+", модель: "+this.getModel()+", гоночная: "+this.isRaceCar+")";
    }
    public void setRaceCar(boolean raceCar) { //setter - установка значения
        isRaceCar = raceCar;
    }
    public boolean isRaceCar() { //getter - возвращает переменную
        return isRaceCar;
    }
}
//получить доступ к переменным
//изменить закрытое значение