package option2;
import java.io.*;
import java.util.*;

public class TravelingSalesman {
    static private Random r = new Random();
    private int numCities = 0;
    private ArrayList<String> cities = null;
    private int[][] distances = null;
    private int numVisits = 0;
    private ArrayList<String> visits = null;

    private int numIndividuals = 0;
    private int numGenerations = 0;
    private float crossoverProb = 0.8F;
    private float mutationProb = 0.0F;
    private float inversionProb = 0.0F;

    private ArrayList<Individual> population = null;

    public TravelingSalesman(String filename) {
        readData(filename);
        population = new ArrayList<>(numIndividuals);
        for (int i = 0; i < numIndividuals; i++)
            population.add(new Individual(visits));
    }

    private int calculateDistance(Individual ind) {
        int d = 0;
        d += distances[cities.indexOf("Madrid")][cities.indexOf(ind.getCity(0))];

        for (int i = 1; i < ind.getLength(); i++)
            d += distances[cities.indexOf(ind.getCity(i - 1))][cities.indexOf(ind.getCity(i))];

        d += distances[cities.indexOf(ind.getCity(ind.getLength() - 1))][cities.indexOf("Madrid")];
        return d;
    }

    private Individual tournament() {
        Individual best = null;
        int minD = Integer.MAX_VALUE;
        for (int i = 0; i < 3; i++) {
            Individual candidate = population.get(r.nextInt(population.size()));
            int d = calculateDistance(candidate);
            if (d < minD) {
                minD = d;
                best = candidate;
            }
        }
        return best;
    }

    public void evolve() {
        int generation = 1;

        while (generation <= numGenerations) {
            ArrayList<Individual> newPopulation = new ArrayList<>();

            Individual bestIndividual = population.get(0);
            int bestDist = calculateDistance(bestIndividual);
            for (Individual i : population) {
                int d = calculateDistance(i);
                if (d < bestDist) {
                    bestDist = d;
                    bestIndividual = i;
                }
            }
            newPopulation.add(new Individual(bestIndividual));

            while (newPopulation.size() < numIndividuals) {
                Individual parent1 = tournament();
                Individual parent2 = tournament();
                Individual offspring;

                if (r.nextFloat() <= crossoverProb) {
                    offspring = parent1.orderedUniformCrossover(parent2);
                } else {
                    offspring = new Individual(parent1);
                }

                if (r.nextFloat() <= mutationProb) {
                    offspring.swap();
                }

                if (r.nextFloat() <= inversionProb) {
                    String c1 = offspring.getRandomCity();
                    String c2 = offspring.getDifferentCity(c1);
                    offspring.invert(c1, c2);
                }

                newPopulation.add(offspring);
            }
            population = newPopulation;
            System.out.println("Generation " + generation + " - Best distance: " + bestDist);
            generation++;
        }
        showResult();
    }

    private void showResult() {
        Individual best = null;
        int min = Integer.MAX_VALUE;
        for (Individual i : population) {
            int d = calculateDistance(i);
            if (d < min) {
                min = d;
                best = i;
            }
        }
        System.out.println("\nFINISHED. Best solution found: " + min + " Km");
        System.out.println("Route: " + best.toString());
    }

    private void readData(String filename) {
        Scanner sc = null;
        try {
            sc = new Scanner(new File(filename));
            sc.useLocale(Locale.US);

            while (!sc.next().contains("="));
            this.numCities = sc.nextInt();
            sc.nextLine();

            cities = new ArrayList<>(this.numCities);
            for (int i = 0; i < this.numCities; i++) {
                String line = sc.nextLine().trim();
                if (line.isEmpty()) {
                    i--;
                    continue;
                }
                cities.add(line);
            }

            distances = new int[this.numCities][this.numCities];
            for (int i = 0; i < this.numCities; i++) {
                for (int j = 0; j < this.numCities; j++) {
                    if (sc.hasNextInt()) {
                        distances[i][j] = sc.nextInt();
                    }
                }
            }

            while (!sc.next().contains("="));
            this.numVisits = sc.nextInt();
            sc.nextLine();

            visits = new ArrayList<>(this.numVisits);
            for (int i = 0; i < this.numVisits; i++) {
                String line = sc.nextLine().trim();
                if (line.isEmpty()) {
                    i--;
                    continue;
                }
                visits.add(line);
            }

            while (!sc.next().contains("="));
            this.numIndividuals = sc.nextInt();

            while (!sc.next().contains("="));
            this.numGenerations = sc.nextInt();

            while (!sc.next().contains("="));
            String floatStr = sc.next().replace(",", ".");
            this.inversionProb = Float.parseFloat(floatStr);

            while (!sc.next().contains("="));
            floatStr = sc.next().replace(",", ".");
            this.mutationProb = Float.parseFloat(floatStr);

        } catch (Exception e) {
            System.out.println("Error reading file: " + e.toString());
            e.printStackTrace();
            System.exit(0);
        } finally {
            if (sc != null) sc.close();
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java TravelingSalesman <filename>");
            System.exit(0);
        }
        TravelingSalesman salesman = new TravelingSalesman(args[0]);
        salesman.evolve();
    }
}