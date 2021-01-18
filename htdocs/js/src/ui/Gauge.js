 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

'use strict';

export class Gauge extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
	}
	
	render() {
		let min_a = 0.5 * 3.14 + 0.3;
		let max_a = 2.5 * 3.14 - 0.3;
		let a = min_a + (max_a - min_a) * this.props.fill / this.props.capacity;
		
		return (
			<div className="Gauge">
				<div className="needle" style={{rotate: a+'rad'}}></div>
			</div>
		);
	}
}
