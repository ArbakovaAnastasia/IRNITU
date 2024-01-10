public class AUDI extends Car { //ауди наследник класса машина
    public AUDI(String number, String color, String model) {
        super(number, color, model); //супер конструктор, который уже находится в абстрактном классе
    }
    @Override //перезапись метода
    public void beep(){
        System.out.println("Бип-бип! Это AUDI!");
    }
}
