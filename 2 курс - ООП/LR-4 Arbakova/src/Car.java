public abstract class Car { //абстрактный класс машина
    private String number;
    private String color;
    private String model;

    public Car(String number, String color, String model) { //конструктор
        this.number = number;
        this.color = color;
        this.model = model;
    }

    @Override
    public String toString() {
        String[] classInfo = this.getClass().toString().split(" ");
        return classInfo[1]+ " (Номер: "+number+", цвет: "+color+", модель: "+model+")";
    }

    public void beep(){
        System.out.println("Бип-бип! Это неизвестная машинка!");
    }

    //getters setters
    public String getNumber() {
        return number;
    }

    public void setNumber(String number) {
        this.number = number;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }
}
