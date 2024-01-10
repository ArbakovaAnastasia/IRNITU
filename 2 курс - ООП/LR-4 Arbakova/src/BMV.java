public class BMV extends Car { //бмв наследник класса машина
    public BMV(String number, String color, String model) {
        super(number, color, model); //супер конструктор, который уже находится в абстрактном классе
    }
    @Override //перезапись метода
    public void beep(){
        System.out.println("Бип-бип! Это БМВ!");
    }

}
