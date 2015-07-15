/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package clonalg_metamodel.problems;

import clonalg_metamodel.base.ConstrainedProblem;
import clonalg_metamodel.base.Problem;
import clonalg_metamodel.util.Configuration;

/**
 *
 * @author hedersb
 */
public class F37CalculadorFortran25BarDiscrete extends Problem implements ConstrainedProblem {

    public static int primeiraVez = 1;
    private int dimension;
    private double[][] bound = null;
    private Configuration configuration;
    protected double[] boundBase = {0, 32};
    private double[] barra_25;
    private int mapeamento[];
    private double rho;
    private double[] tab = {
	0.1,
	0.1,
	0.2,
	0.3,
	0.4,
	0.5,
	0.6,
	0.7,
	0.8,
	0.9,
	1.0,
	1.1,
	1.2,
	1.3,
	1.4,
	1.5,
	1.6,
	1.7,
	1.8,
	1.9,
	2.0,
	2.1,
	2.2,
	2.3,
	2.4,
	2.5,
	2.6,
	2.8,
	3.0,
	3.2,
	3.4,
	3.4
    };

    public F37CalculadorFortran25BarDiscrete(Configuration configuration) {
	rho = 0.1;
	this.dimension = 16;
	this.configuration = configuration;
	barra_25 = new double[25];
	barra_25[           0] = 75.000000000000000;      // comprimento da barra           1
	barra_25[           1] = 130.50383136138188;      // comprimento da barra           2
	barra_25[           2] = 130.50383136138188;      // comprimento da barra           3
	barra_25[           3] = 130.50383136138188;      // comprimento da barra           4
	barra_25[           4] = 130.50383136138188;      // comprimento da barra           5
	barra_25[           5] = 106.80004681646913;      // comprimento da barra           6
	barra_25[           6] = 106.80004681646913;      // comprimento da barra           7
	barra_25[           7] = 106.80004681646913;      // comprimento da barra           8
	barra_25[           8] = 106.80004681646913;      // comprimento da barra           9
	barra_25[           9] = 75.000000000000000;      // comprimento da barra          10
	barra_25[          10] = 75.000000000000000;      // comprimento da barra          11
	barra_25[          11] = 75.000000000000000;      // comprimento da barra          12
	barra_25[          12] = 75.000000000000000;      // comprimento da barra          13
	barra_25[          13] = 181.14220932736799;      // comprimento da barra          14
	barra_25[          14] = 181.14220932736799;      // comprimento da barra          15
	barra_25[          15] = 181.14220932736799;      // comprimento da barra          16
	barra_25[          16] = 181.14220932736799;      // comprimento da barra          17
	barra_25[          17] = 181.14220932736799;      // comprimento da barra          18
	barra_25[          18] = 181.14220932736799;      // comprimento da barra          19
	barra_25[          19] = 181.14220932736799;      // comprimento da barra          20
	barra_25[          20] = 181.14220932736799;      // comprimento da barra          21
	barra_25[          21] = 133.46347815039138;      // comprimento da barra          22
	barra_25[          22] = 133.46347815039138;      // comprimento da barra          23
	barra_25[          23] = 133.46347815039138;      // comprimento da barra          24
	barra_25[          24] = 133.46347815039138;      // comprimento da barra          25
	mapeamento = new int[9];
	mapeamento[0] = 0;
	mapeamento[1] = 1;
	mapeamento[2] = 5;
	mapeamento[3] = 9;
	mapeamento[4] = 11;
	mapeamento[5] = 13;
	mapeamento[6] = 17;
	mapeamento[7] = 21;
	mapeamento[8] = 25;
    }

    public double evaluate(double[] gene) {
	double weight = 0;
	int k = 0;
	int k1 = 1;
	for(int i = 0; i<barra_25.length; i++) {
	    if (mapeamento[k1] == i) {
		k++;
		k1++;
	    }
	    weight += barra_25[i] * tab[(int) Math.floor(gene[k])] ;
	}
	return weight*rho;
    }

    @Override
    protected double[] evaluateSolution(Object gene) {
	double[] x = null;
	if (gene instanceof double[]) {
	    x = (double[]) gene;
	} else {
	    int[] variableSize = new int[getNumberOfVariables()];
	    for (int i = 0; i < variableSize.length; i++) {
		variableSize[i] = configuration.getBinaryEncodingContinuousVariable();
	    }
	    x = configuration.getUtilitaries().getRealFromBinary((boolean[]) gene, variableSize, getBounds(), true, configuration.getBinaryEncodingContinuousVariable(), this);
	}
	double[] g = new double[x.length];
	int i = 0;
        int id;
	for (double d : x) {
	    //x[i] = tab[(int)Math.round(d)];
            id = (int) Math.floor(d);
	    g[i] = tab[id < tab.length? id: tab.length-1];
	    i++;
	}
	//long t = System.currentTimeMillis();
	double restricoes[] = new double[29];
	double funcaoObjetiva = calcula25Bar(g, restricoes, primeiraVez);
	primeiraVez = 0;
	double retorno[] = new double[restricoes.length + 1];
	retorno[0] = funcaoObjetiva;
	for (i = 0; i < restricoes.length; i++) {
	    retorno[i + 1] = restricoes[i];
	}
	//System.out.println("Tempo " + (System.currentTimeMillis()-t));
	return retorno;
    }

    @Override
    public double[][] getBounds() {
	if (bound == null) {
	    bound = new double[dimension][2];
	    for (int i = 0; i < bound.length; i++) {
		bound[i][0] = boundBase[0];
		bound[i][1] = boundBase[1];
	    }
	}
	return bound;
    }

    @Override
    public int getMaxNumberFitnessFuntionEvaluation() {
	return 12000;
	//return 1000000;
    }

    @Override
    public double getBestValue() {
	throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Problem clone() {
	return new F37CalculadorFortran25BarDiscrete(configuration);
    }

    private native double calcula25Bar(double[] x, double restricoes[], int flap);

    static {
	System.loadLibrary("Calcula25Bar");
    }

}
