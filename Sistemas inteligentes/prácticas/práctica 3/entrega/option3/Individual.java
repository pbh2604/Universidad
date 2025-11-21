package option3;
import java.util.*;
/*ejecutar:
    javac option3/*.java
    java option3.TravelingSalesman DatosPru1.txt
*/ 

public class Individual {
    static private Random r = new Random();
    private ArrayList<String> chromosome = null;

    public Individual(ArrayList<String> visits) {
        this.chromosome = new ArrayList<>(visits);
        Collections.shuffle(this.chromosome);
    }

    public Individual(Individual individual) {
        this.chromosome = new ArrayList<>(individual.chromosome);
    }

    public int getLength() {
        return chromosome.size();
    }

    public String getCity(int pos) {
        return chromosome.get(pos);
    }

    public String getRandomCity() {
        return chromosome.get(r.nextInt(chromosome.size()));
    }

    public String getDifferentCity(String city) {
        boolean found = false;
        String tempCity = null;
        while (!found) {
            tempCity = chromosome.get(r.nextInt(chromosome.size()));
            if (city.compareTo(tempCity) != 0)
                found = true;
        }
        return tempCity;
    }

    public void invert(String c1, String c2) {
        int pos1 = chromosome.indexOf(c1);
        int pos2 = chromosome.indexOf(c2);
        
        if (pos1 > pos2) {
            int temp = pos1;
            pos1 = pos2;
            pos2 = temp;
        }
        
        ArrayList<String> before = new ArrayList<>(chromosome.subList(0, pos1));
        ArrayList<String> middle = new ArrayList<>(chromosome.subList(pos1, pos2 + 1));
        ArrayList<String> after = new ArrayList<>(chromosome.subList(pos2 + 1, chromosome.size()));
        
        Collections.reverse(middle);
        
        chromosome.clear();
        chromosome.addAll(before);
        chromosome.addAll(middle);
        chromosome.addAll(after);
    }

    public void swap() {
        int pos1 = r.nextInt(chromosome.size());
        int pos2 = r.nextInt(chromosome.size());
        if (pos1 != pos2) {
            Collections.swap(chromosome, pos1, pos2);
        }
    }

    @Override
    public String toString() {
        StringBuilder msg = new StringBuilder("( ");
        for (String s : chromosome)
            msg.append(s).append(" ");
        msg.append(")");
        return msg.toString();
    }
}