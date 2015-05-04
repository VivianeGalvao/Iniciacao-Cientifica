/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package clonalg_metamodel.problems;

import clonalg_metamodel.base.Problem;

/**
 *
 * @author hedersb
 */
public class G01Problem extends Problem {

    @Override
    protected double[] evaluateSolution(Object gene) {

	double[] x = null;
        if (gene instanceof double[]) {
            x = (double[]) gene;
        } else {
            throw new UnsupportedOperationException(
		"G01 problem not implementated for non-real encoded."
	    );
        }

	// Dimension = 13
        double[] g = new double[9];
        double[] f = new double[10];

        int j;

        f[0] = 5.0 * (x[0] + x[1] + x[2] + x[3]) -
                5.0 * (x[0] * x[0] + x[1] * x[1] + x[2] * x[2] + x[3] * x[3]);
        for (j = 4; j < 13; j++) {
            f[0] = f[0] - x[j];
        }

        g[0] = 2.0 * x[0] + 2.0 * x[1] + x[9] + x[10] - 10.;
        g[1] = 2.0 * x[0] + 2.0 * x[2] + x[9] + x[11] - 10.;
        g[2] = 2.0 * x[1] + 2.0 * x[2] + x[10] + x[11] - 10.;
        g[3] = -8.0 * x[0] + x[9];
        g[4] = -8.0 * x[1] + x[10];
        g[5] = -8.0 * x[2] + x[11];
        g[6] = -2.0 * x[3] - x[4] + x[9];
        g[7] = -2.0 * x[5] - x[6] + x[10];
        g[8] = -2.0 * x[7] - x[8] + x[11];

        // Prepare the values to return

        for (j = 0; j < 9; j++) {
            f[j + 1] = g[j]; // Here, all values are just returned "as they are"
        }
        return f;
    }

    @Override
    public double[][] getBounds() {
	double[][] bounds = new double[13][2];
	for (int i = 0; i < 9; i++) {
	    bounds[i][0] = 0;
	    bounds[i][1] = 1;
	}
	for (int i = 9; i < 12; i++) {
	    bounds[i][0] = 0;
	    bounds[i][1] = 100;
	}
	bounds[12][0] = 0;
	bounds[12][1] = 1;
	return bounds;
    }

    @Override
    public int getMaxNumberFitnessFuntionEvaluation() {
	return 500000;
    }

    @Override
    public double getBestValue() {
	return -15;
    }

    @Override
    public Problem clone() {
	return new G01Problem();
    }
}
