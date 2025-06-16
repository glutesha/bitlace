<script lang="ts">
  import { currentDisplay, SIZE , updateDisplay} from '../display';

  function onClick () {
    currentDisplay.set(Array.from({ length: SIZE }, () => Array.from({ length: SIZE }, () => false)))
    updateDisplay();
  };

</script>

<button on:click={onClick} class="bg-cyan-800 hover:bg-cyan-900 active:bg-cyan-950 rounded-3xl size-xl text-white px-5 py-3 text-3xl shadow-2xl font-bold shadow-neutral-900">Erase</button>