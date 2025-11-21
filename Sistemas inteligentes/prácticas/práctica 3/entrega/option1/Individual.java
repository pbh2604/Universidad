package option1;
import java.util.*;
/*ejecutar:
    javac option1/*.java
    java option1.TravelingSalesman DatosPru1.txt
*/ 

public class Individual {
    static private Random r = new Random();
    private ArrayList<String> chromosome = null;

    public Individual() {
        this.chromosome = new ArrayList<String>();
    }

    public Individual(ArrayList<String> visits) {
        this.chromosome = new ArrayList<String>(visits);
        Collections.shuffle(this.chromosome);
    }

    public Individual(Individual individual) {
        this.chromosome = new ArrayList<String>(individual.chromosome);
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

    public Individual crossoverPMX(Individual partner) {
        Individual offspring = new Individual();
        int size = this.getLength();
        ArrayList<String> offspringGenes = new ArrayList<>(Collections.nCopies(size, null));

        int point1 = r.nextInt(size);
        int point2 = r.nextInt(size);
        if (point1 > point2) {
            int aux = point1;
            point1 = point2;
            point2 = aux;
        }

        for (int i = point1; i <= point2; i++) {
            offspringGenes.set(i, this.chromosome.get(i));
        }

        for (int i = point1; i <= point2; i++) {
            String geneP2 = partner.chromosome.get(i);
            if (!offspringGenes.contains(geneP2)) {
                int pos = i;
                while (pos >= point1 && pos <= point2) {
                    String valP1 = this.chromosome.get(pos);
                    pos = partner.chromosome.indexOf(valP1);
                }
                offspringGenes.set(pos, geneP2);
            }
        }

        for (int i = 0; i < size; i++) {
            if (offspringGenes.get(i) == null) {
                offspringGenes.set(i, partner.chromosome.get(i));
            }
        }

        offspring.chromosome = offspringGenes;
        return offspring;
    }

    public void invert(String c1, String c2) {
        int pos1 = chromosome.indexOf(c1);
        int pos2 = chromosome.indexOf(c2);

        if (pos1 == -1 || pos2 == -1 || pos1 == pos2) return;

        if (pos1 > pos2) {
            int temp = pos1;
            pos1 = pos2;
            pos2 = temp;
        }

        ArrayList<String> subList = new ArrayList<>();
        for (int i = pos1; i <= pos2; i++) {
            subList.add(chromosome.get(i));
        }

        Collections.reverse(subList);

        for (int i = 0; i < subList.size(); i++) {
            chromosome.set(pos1 + i, subList.get(i));
        }
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
        for (String s : chromosome) msg.append(s).append(" ");
        msg.append(")");
        return msg.toString();
    }
}