package option3;
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
    private float inversionProb = 0.0F;
    private float mutationProb = 0.0F;

    private ArrayList<ArrayList<Individual>> archipelago = null;
    private int numIslands = 3;
    private int migrationFrequency = 10;
    private int numMigrants = 2;

    public TravelingSalesman(String filename) {
        readData(filename);
        archipelago = new ArrayList<>();

        for (int k = 0; k < numIslands; k++) {
            ArrayList<Individual> island = new ArrayList<>();
            for (int i = 0; i < numIndividuals; i++)
                island.add(new Individual(visits));
            archipelago.add(island);
        }
    }

    private int calculateDistance(Individual ind) {
        int d = 0;
        d += distances[cities.indexOf("Madrid")][cities.indexOf(ind.getCity(0))];
        for (int i = 1; i < ind.getLength(); i++)
            d += distances[cities.indexOf(ind.getCity(i - 1))][cities.indexOf(ind.getCity(i))];
        d += distances[cities.indexOf(ind.getCity(ind.getLength() - 1))][cities.indexOf("Madrid")];
        return d;
    }

    public void evolve() {
        int generation = 1;
        while (generation <= numGenerations) {
            for (int k = 0; k < numIslands; k++) {
                ArrayList<Individual> island = archipelago.get(k);
                ArrayList<Individual> newIsland = new ArrayList<>();

                for (int i = 0; i < numIndividuals; i++) {
                    Individual parent = island.get(r.nextInt(island.size()));
                    Individual offspring = new Individual(parent);

                    if (r.nextFloat() <= inversionProb) {
                        String c1 = offspring.getRandomCity();
                        offspring.invert(c1, offspring.getDifferentCity(c1));
                    }
                    if (r.nextFloat() <= mutationProb) {
                        offspring.swap();
                    }

                    if (calculateDistance(offspring) < calculateDistance(parent)) {
                        newIsland.add(offspring);
                    } else {
                        newIsland.add(parent);
                    }
                }
                archipelago.set(k, newIsland);
            }

            if (generation % migrationFrequency == 0) {
                migrate();
            }

            showGlobalBest(generation);
            generation++;
        }
    }

    private void migrate() {
        System.out.println(">>> [ISLAND MIGRATION]");
        for (int i = 0; i < numIslands; i++) {
            int neighbor = (i + 1) % numIslands;
            ArrayList<Individual> origin = archipelago.get(i);
            ArrayList<Individual> destination = archipelago.get(neighbor);

            origin.sort(Comparator.comparingInt(this::calculateDistance));

            for (int m = 0; m < numMigrants; m++) {
                Individual migrant = new Individual(origin.get(m));
                destination.set(r.nextInt(destination.size()), migrant);
            }
        }
    }

    private void showGlobalBest(int gen) {
        int globalMin = Integer.MAX_VALUE;
        for (ArrayList<Individual> island : archipelago) {
            for (Individual i : island) {
                int d = calculateDistance(i);
                if (d < globalMin) globalMin = d;
            }
        }
        System.out.println("Generation " + gen + " - Global Best: " + globalMin + " Km");
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
        new TravelingSalesman(args[0]).evolve();
    }
}