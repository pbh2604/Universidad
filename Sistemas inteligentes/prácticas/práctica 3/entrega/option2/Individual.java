package option2;
import java.util.*;
/*ejecutar:
    javac option2/*.java
    java option2.TravelingSalesman DatosPru1.txt
*/ 

public class Individual {
    static private Random r = new Random();
    private ArrayList<String> chromosome = null;

    public Individual() {
        this.chromosome = new ArrayList<>();
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

    public Individual orderedUniformCrossover(Individual partner) {
        Individual offspring = new Individual();
        int size = this.getLength();
        ArrayList<String> offspringGenes = new ArrayList<>(Collections.nCopies(size, null));

        boolean[] template = new boolean[size];
        ArrayList<String> copiedGenes = new ArrayList<>();

        for (int i = 0; i < size; i++) {
            template[i] = r.nextBoolean();
            if (template[i]) {
                String gene = this.chromosome.get(i);
                offspringGenes.set(i, gene);
                copiedGenes.add(gene);
            }
        }

        int idxP2 = 0;
        for (int i = 0; i < size; i++) {
            if (offspringGenes.get(i) == null) {
                String candidateGene = null;
                while (candidateGene == null && idxP2 < size) {
                    String temp = partner.chromosome.get(idxP2++);
                    if (!copiedGenes.contains(temp)) {
                        candidateGene = temp;
                    }
                }
                offspringGenes.set(i, candidateGene);
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
            int aux = pos1;
            pos1 = pos2;
            pos2 = aux;
        }

        ArrayList<String> sub = new ArrayList<>(chromosome.subList(pos1, pos2 + 1));
        Collections.reverse(sub);

        for (int i = 0; i < sub.size(); i++) {
            chromosome.set(pos1 + i, sub.get(i));
        }
    }

    public void swap() {
        int pos1 = r.nextInt(chromosome.size());
        int pos2 = r.nextInt(chromosome.size());
        if (pos1 != pos2) {
            Collections.swap(chromosome, pos1, pos2);
        }
    }

    public String getRandomCity() {
        return chromosome.get(r.nextInt(chromosome.size()));
    }

    public String getDifferentCity(String city) {
        String temp;
        do {
            temp = getRandomCity();
        } while (temp.equals(city));
        return temp;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("(");
        for (String s : chromosome) sb.append(" ").append(s);
        sb.append(" )");
        return sb.toString();
    }
}