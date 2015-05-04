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
public class F33CalculadorFortran10Bar extends Problem implements ConstrainedProblem {

    public static int primeiraVez = 1;
    protected int dimension;
    protected double[][] bound = null;
    private Configuration configuration;
    protected double[] boundBase = {0.1, 40};
    private double[] barra_10;
    private double rho;

    public F33CalculadorFortran10Bar(Configuration configuration) {
	rho = 0.1;
	this.dimension = 10;
	this.configuration = configuration;
	barra_10 = new double[10];
	barra_10[           0] = 360.00000;     // comprimento da barra           1
	barra_10[           1] = 360.00000;     // comprimento da barra           2
	barra_10[           2] = 360.00000;     // comprimento da barra           3
	barra_10[           3] = 360.00000;     // comprimento da barra           4
	barra_10[           4] = 360.00000;     // comprimento da barra           5
	barra_10[           5] = 360.00000;     // comprimento da barra           6
	barra_10[           6] = 509.11688;     // comprimento da barra           7
	barra_10[           7] = 509.11688;     // comprimento da barra           8
	barra_10[           8] = 509.11688;     // comprimento da barra           9
	barra_10[           9] = 509.11688;     // comprimento da barra          10
    }

    public double evaluate(double[] gene) {
	double weight = 0;
	for (int i = 0; i < barra_10.length; i++) {
	    weight += barra_10[i] * gene[i];
	}
	return weight * rho;
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
	//long t = System.currentTimeMillis();
	double restricoes[] = new double[18];
	double funcaoObjetiva = calcula10Bar(x, restricoes, primeiraVez);
	primeiraVez = 0;
	double retorno[] = new double[restricoes.length + 1];
	retorno[0] = funcaoObjetiva;
	for (int i = 0; i < restricoes.length; i++) {
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
    }

    @Override
    public double getBestValue() {
	throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Problem clone() {
	return new F33CalculadorFortran10Bar(configuration);
    }

    private native double calcula10Bar(double[] x, double restricoes[], int flap);

    static {
	System.loadLibrary("Calcula10Bar");
    }
}
