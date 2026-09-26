from pulp import value, PULP_CBC_CMD
import copy


def find_allowable_increase(
    base_model, var_name, base_coef, step=10, max_iter=50, verbose=True
):
    """
    Helper function to estimate the allowable increase for a variable's objective coefficient.

    Parameters:
        base_model (LpProblem): The PuLP model with constraints and variables defined.
        var_name (str): The name of the variable for which to compute the allowable increase.
        base_coef (float): The initial coefficient of the variable in the objective function.
        step (float): Increment to increase the coefficient in each iteration.
        max_iter (int): Maximum number of iterations to test.

    Returns:
        allowable_increase (float): The maximum increase in the coefficient without changing the optimal basis.
    """
    # Copy the base model to avoid modifying the original
    model = copy.deepcopy(base_model)

    # Extract the variable of interest
    target_var = None
    for var in model.variables():
        if var.name == var_name:
            target_var = var
            break

    if target_var is None:
        raise ValueError(f"Variable '{var_name}' not found in the model.")

    # Store the base solution
    model.solve(PULP_CBC_CMD(msg=0))
    base_solution = {var.name: var.varValue for var in model.variables()}

    # Iteratively adjust the coefficient
    for i in range(max_iter):
        current_coef = base_coef + i * step

        # Update the objective function with the new coefficient
        model += model.objective + (current_coef - base_coef) * target_var

        # Solve the model
        model.solve()

        # Get current solution and objective value
        current_solution = {var.name: var.varValue for var in model.variables()}
        current_objective = value(model.objective)

        # Print results for intuition
        if verbose:
            print(
                f"Iteration {i + 1}: Coefficient of {var_name}: {current_coef}, Objective value: {current_objective}, Solution: {current_solution}"
            )
            print("-" * 40)

        # Check if the solution has changed
        if current_solution != base_solution:
            print(f"Optimal basis changed at coefficient {current_coef}.\n")
            return current_coef - base_coef

        # Reset the objective function
        model.objective -= (current_coef - base_coef) * target_var

    return None  # Return None if no change is observed within max_iter
